/*
 * File:   collision.cpp
 * Author: Nick (original version), ahnonay (SFML2 compatibility), Paweł Syska (C++17 refactor + naming convention)
 */
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <array>
#include "Collision.h"

namespace Collision
{
	using TextureMask = std::vector<sf::Uint8>;

	static sf::Uint8 getPixel(const TextureMask& mask, const sf::Texture& tex, uint32_t x, uint32_t y) {
		if (x > tex.getSize().x || y > tex.getSize().y)
			return 0;

		return mask[x + y * tex.getSize().x];
	}

	class BitmaskRegistry
	{
	public:

		auto& create(const sf::Texture& tex, const sf::Image& img) {
			auto mask = TextureMask(tex.getSize().y * tex.getSize().x);

			for (uint32_t y = 0; y < tex.getSize().y; ++y)
			{
				for (uint32_t x = 0; x < tex.getSize().x; ++x)
					mask[x + y * tex.getSize().x] = img.getPixel(x, y).a;
			}

			// store and return ref to the mask
			return (bitmasks[&tex] = std::move(mask));
		}

		auto& get(const sf::Texture& tex) {
			auto pair = bitmasks.find(&tex);
			if (pair == bitmasks.end())
			{
				return create(tex, tex.copyToImage());
			}

			return pair->second;
		}

		
	private:
		std::map<const sf::Texture*, TextureMask> bitmasks;
	};

	// Gets global instance of BitmaskRegistry.
	// "static" to make sure this function doesn't leak to other source file
	static BitmaskRegistry& bitmasks() {
		static BitmaskRegistry instance; // Initialize the reference variable with an instance
		return instance;
	}

	bool singlePixelTest(const sf::Sprite& sprite, sf::Vector2f& mousePosition, sf::Uint8 alphaLimit) {
		if (!sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			return false;

		auto subRect = sprite.getTextureRect();
		auto& mask = bitmasks().get(*sprite.getTexture());

		auto sv = sprite.getInverseTransform().transformPoint(mousePosition.x, mousePosition.y);
		// Make sure pixels fall within the sprite's subrect
		if (sv.x > 0 && sv.y > 0 && sv.x < subRect.width && sv.y < subRect.height) {
			return getPixel(mask, *sprite.getTexture(), static_cast<int>(sv.x) + subRect.left, static_cast<int>(sv.y) + subRect.top) > alphaLimit;
		}
		return false;
	}

	bool pixelPerfectTest(const sf::Sprite& sprite1, const sf::Sprite& sprite2, sf::Uint8 alphaLimit) {
		sf::FloatRect intersection;
		if (!sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds(), intersection))
			return false;

		auto s1SubRect = sprite1.getTextureRect();
		auto s2SubRect = sprite2.getTextureRect();

		auto& mask1 = bitmasks().get(*sprite1.getTexture());
		auto& mask2 = bitmasks().get(*sprite2.getTexture());

		// Loop through our pixels
		for (auto i = intersection.left; i < intersection.left + intersection.width; ++i) {
			for (auto j = intersection.top; j < intersection.top + intersection.height; ++j) {

				auto s1v = sprite1.getInverseTransform().transformPoint(i, j);
				auto s2v = sprite2.getInverseTransform().transformPoint(i, j);

				// Make sure pixels fall within the sprite's subrect
				if (s1v.x > 0 && s1v.y > 0 && s2v.x > 0 && s2v.y > 0 &&
					s1v.x < s1SubRect.width && s1v.y < s1SubRect.height &&
					s2v.x < s2SubRect.width && s2v.y < s2SubRect.height) {

					if (getPixel(mask1, *sprite1.getTexture(), (int)(s1v.x) + s1SubRect.left, (int)(s1v.y) + s1SubRect.top) > alphaLimit &&
						getPixel(mask2, *sprite2.getTexture(), (int)(s2v.x) + s2SubRect.left, (int)(s2v.y) + s2SubRect.top) > alphaLimit)
						return true;

				}
			}
		}
		return false;
	}

	bool createTextureAndBitmask(sf::Texture& loadInto, const std::string& filename)
	{
		auto img = sf::Image();
		if (!img.loadFromFile(filename))
			return false;
		if (!loadInto.loadFromImage(img))
			return false;

		bitmasks().create(loadInto, img);
		return true;
	}

	sf::Vector2f getSpriteCenter(const sf::Sprite& sprite)
	{
		auto AABB = sprite.getGlobalBounds();
		return sf::Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
	}

	sf::Vector2f getSpriteSize(const sf::Sprite& sprite)
	{
		auto originalSize = sprite.getTextureRect();
		auto scale = sprite.getScale();
		return sf::Vector2f(originalSize.width * scale.x, originalSize.height * scale.y);
	}

	bool circleTest(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
		auto spr1Size = getSpriteSize(sprite1);
		auto spr2Size = getSpriteSize(sprite2);
		auto radius1 = (spr1Size.x + spr1Size.y) / 4.f;
		auto radius2 = (spr2Size.x + spr2Size.y) / 4.f;

		auto diff = getSpriteCenter(sprite1) - getSpriteCenter(sprite2);

		return (diff.x * diff.x + diff.y * diff.y <= (radius1 + radius2) * (radius1 + radius2));
	}

	struct OrientedBoundingBox // Used in the BoundingBoxTest
	{
		std::array<sf::Vector2f, 4> points;

		OrientedBoundingBox(const sf::Sprite& sprite) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
		{
			auto transform = sprite.getTransform();
			auto local = sprite.getTextureRect();
			points[0] = transform.transformPoint(0.f, 0.f);
			points[1] = transform.transformPoint(local.width, 0.f);
			points[2] = transform.transformPoint(local.width, local.height);
			points[3] = transform.transformPoint(0.f, local.height);
		}

		// Project all four points of the OBB onto the given axis and return the dot products of the two outermost points
		void projectOntoAxis(const sf::Vector2f& axis, float& min, float& max)
		{
			min = (points[0].x * axis.x + points[0].y * axis.y);
			max = min;
			for (int j = 1; j < points.size(); ++j)
			{
				auto projection = points[j].x * axis.x + points[j].y * axis.y;

				if (projection < min)
					min = projection;
				if (projection > max)
					max = projection;
			}
		}
	};

	bool boundingBoxTest(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
		auto OBB1 = OrientedBoundingBox(sprite1);
		auto OBB2 = OrientedBoundingBox(sprite2);

		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		auto axes = std::array<sf::Vector2f, 4>{
			sf::Vector2f(OBB1.points[1].x - OBB1.points[0].x, OBB1.points[1].y - OBB1.points[0].y),
				sf::Vector2f(OBB1.points[1].x - OBB1.points[2].x, OBB1.points[1].y - OBB1.points[2].y),
				sf::Vector2f(OBB2.points[0].x - OBB2.points[3].x, OBB2.points[0].y - OBB2.points[3].y),
				sf::Vector2f(OBB2.points[0].x - OBB2.points[1].x, OBB2.points[0].y - OBB2.points[1].y)
		};

		for (auto& axis : axes)
		{
			float minOBB1, maxOBB1, minOBB2, maxOBB2;

			// Project the points of both OBBs onto the axis ...
			OBB1.projectOntoAxis(axis, minOBB1, maxOBB1);
			OBB2.projectOntoAxis(axis, minOBB2, maxOBB2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
			if (!((minOBB2 <= maxOBB1) && (maxOBB2 >= minOBB1)))
				return false;
		}
		return true;
	}
}