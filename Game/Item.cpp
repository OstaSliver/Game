#include "Item.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Item::Item(const sf::Vector2f& pos, ItemType itemType) : position(pos), type(itemType) {
	
	if (!textureExp.loadFromFile("Resource/sprite/Item/Rename.png") && type == ItemType::EXP) {
		std::cerr << "Error loading player texture: " << std::endl;
	}

	if (!textureHp.loadFromFile("Resource/sprite/Item/HP.png") && type == ItemType::HP) {
		std::cerr << "Error loading player texture: " << std::endl;
	}

	item.setScale(0.2, 0.2);
	item.setPosition(position);
}

ItemType Item::getType() {
	return type;
}

void Item::draw(sf::RenderWindow& window) {
	if(type == ItemType::EXP)
		item.setTexture(textureExp);
	else if(type == ItemType::HP)
		item.setTexture(textureHp);

	window.draw(item);
}

sf::Sprite Item::getPosition() {
	return item;
}