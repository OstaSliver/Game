#pragma once
#include <SFML/Graphics.hpp>

class Map {
private:
    int width;
    int height;
    sf::Texture grassTexture;

    std::vector<sf::Sprite> grassTiles;

public:
    Map(int w, int h);
    void draw(sf::RenderWindow& window);
};