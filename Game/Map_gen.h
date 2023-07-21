#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Map_gen
{
public:
	Map_gen(const std::string& texture_map, int width, int height);

		void draw(sf::RenderWindow& window);

private:
	sf::Sprite Background;
	sf::Texture texture_background;
	int mapWidth, mapHeight;
};
