#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


#include "FireBall.h"

#define M_PI 3.14

FireBall::FireBall(sf::Vector2f& position, sf::Vector2f target) {
	this->Target = target;
	this->direction = this->Target - position;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	this->direction /= length;


	float rotation = atan2(direction.y, direction.x) * 180 / M_PI;

	sprite.setRotation(rotation);

	if (!texture.loadFromFile("Resource/sprite/Skill/FireBall/FB001.png")) {
		std::cerr << "Error loading texture monster" << std::endl;
		return;
	}

	
	sprite.setScale(2,2);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	sprite.setPosition(position);

	//std::cout << "work";
}
void FireBall::updata(float& deltaTime)
{
	elaped += deltaTime;
	if (1.0f < elaped) {
		elaped = 0.0f;
	switch (this->Animation)
	{
	case 0:
		if (!texture.loadFromFile("Resource/sprite/Skill/FireBall/FB001.png")) {
			return;
		}
		this->Animation = 1;
	
	case 1:
		if (!texture.loadFromFile("Resource/sprite/Skill/FireBall/FB002.png")) {
			return;
		}
		this->Animation = 2;

	case 2:
		if (!texture.loadFromFile("Resource/sprite/Skill/FireBall/FB003.png")) {
			return;
		}
		this->Animation = 3;

	case 3:
		if
			(!texture.loadFromFile("Resource/sprite/Skill/FireBall/FB004.png")) {
			return;
		}
		this->Animation = 4;

	case 4:
		if (!texture.loadFromFile("Resource/sprite/Skill/FireBall/FB005.png")) {
			return;
		}
		this->Animation = 0;

	default:
		break;
		}
	}
	

	sprite.move(this->direction * 200.f * deltaTime);
}

void FireBall::draw(sf::RenderWindow& window)
{
	sprite.setTexture(texture);
	window.draw(sprite);
}
