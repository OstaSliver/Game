#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map_gen.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

Map_gen::Map_gen(const std::string& texturePath_Map, int width, int height)
    : mapWidth(width), mapHeight(height)
{
    if (!texture_background.loadFromFile(texturePath_Map))
    {
        std::cout << "Failed to load texture." << std::endl;
        return;
    }

    texture_background.setRepeated(true);
    Background.setTexture(texture_background);
    Background.setTextureRect(sf::IntRect(0, 0, mapWidth, mapHeight));
}

void Map_gen::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < SCREEN_WIDTH; x += mapWidth)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y += mapHeight)
        {
            Background.setPosition(x, y);
            window.draw(Background);
        }
    }
}
