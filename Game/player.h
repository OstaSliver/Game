#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class player
{
public:
    player(const std::string& texturePath, const sf::Vector2f& position);
    void move(const sf::Vector2f& val);
    void draw(sf::RenderWindow& window);
    void takeDamage(int damage);
    void levelUp(int exp_incress);

    sf::Sprite &getSprite();


    int getLevel();
    int getMaxHP();
    int getHP();
    int getMaxExp();
    int getExp();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    int level;
    int max_HP,HP;
    int max_Exp,Exp;
};