#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "Item.h"
#include "Ability.h"

class LevelUpGui
{
public:
	LevelUpGui(sf::RenderWindow& window, Ability* ability,int abilityCanlevelup1,int abilityCanlevelup2);
	void Render(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f& playerPos);
	void setInformationText1();
	void setInformationText2();

	bool isPressButton1(sf::Vector2f mosuePos);
	bool isPressButton2(sf::Vector2f mosuePos);

	void isHoverButton1(sf::Vector2f mosuePos);
	void isHoverButton2(sf::Vector2f mosuePos);

	LevelUpGui(const LevelUpGui&) = delete;
	LevelUpGui& operator=(const LevelUpGui&) = delete;

	int abilityCanlevelup1;
	int abilityCanlevelup2;

private:
	sf::Font font;
	sf::Text levelUpText;
	Ability* ability;

	sf::Sprite sprite1;
	sf::Sprite sprite2;
	sf::Texture texture1;
	sf::Texture texture2;

	sf::RectangleShape Button1;
	sf::RectangleShape Button2;

	sf::Text informationText1;
	sf::Text informationText2;
	sf::Text selectText1;
	sf::Text selectText2;

	sf::RectangleShape levelUpBackground;

};

