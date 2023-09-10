#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"

class player
{
public:
    player(const std::string& texturePath, const sf::Vector2f& position);
    void move(const sf::Vector2f& val);
    void draw(sf::RenderWindow& window);
    void takeDamage(int damage);
    void levelUp(int exp_incress);
    void atk(int baseDamege);
    sf::Sprite &getSprite();


    int getLevel();
    int getMaxHP();
    int getHP();
    int getMaxExp();
    int getExp();
    bool GetDead();

private:
    sf::Texture texture;
    sf::Sprite sprite;

    int level;
    int max_HP,HP;
    int max_Exp,Exp;
    bool isDead = false;
};