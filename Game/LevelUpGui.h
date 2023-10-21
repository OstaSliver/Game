#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "Item.h"
#include "Ability.h"

class LevelUpGui
{
public:
	LevelUpGui(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f& playerPos);
	LevelUpGui(const LevelUpGui&) = delete;
	LevelUpGui& operator=(const LevelUpGui&) = delete;
private:
	sf::Font font;
	sf::Text levelUpText;
	sf::RectangleShape levelUpBackground;

};

