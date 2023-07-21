#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow& window);
	
	void draw(sf::RenderWindow& window);

private:
	sf::Font font;
	sf::Text pauseText;
	sf::Text instructionText;

};

