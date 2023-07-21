#pragma once
#include <SFML/Graphics.hpp>	

class menu
{
public:
	menu();
	void draw(sf::RenderWindow& window);

	bool isPressPlayButton(sf::Vector2f mosuePos);


private:
	sf::Text playText;
	sf::Font font;
	sf::RectangleShape play_button;
};

