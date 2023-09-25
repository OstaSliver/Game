#include "Item.h"
#include <SFML/Graphics.hpp>

Item::Item(const sf::Vector2f& pos, ItemType itemType) : position(pos), type(itemType) {
	
	
	exp.setPosition(position);
}

ItemType Item::getType() {
	return type;
}

void Item::draw(sf::RenderWindow& window) {
	window.draw(exp);
}

sf::Sprite Item::getPosition() {
	return exp;
}