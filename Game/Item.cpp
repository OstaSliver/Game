#include "Item.h"
#include <SFML/Graphics.hpp>

Item::Item(const sf::Vector2f& pos, ItemType itemType) : position(pos), type(itemType) {
	exp.setRadius(20);
	exp.setFillColor(sf::Color::Color(0, 255, 255, 255));
	exp.setPosition(position);
}

ItemType Item::getType() {
	return type;
}

void Item::draw(sf::RenderWindow& window) {
	window.draw(exp);
}

sf::CircleShape Item::getPosition() {
	return exp;
}