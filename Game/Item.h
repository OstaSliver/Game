#pragma once
#include <SFML/Graphics.hpp>

enum class ItemType {
    EXP
};

class Item
{
private:
    sf::Vector2f position;
    sf::Sprite exp;
    ItemType type;


public:
    Item(const sf::Vector2f& pos, ItemType itemType);
    ItemType getType();
    void draw(sf::RenderWindow& window);
    sf::Sprite getPosition();
};