#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "player.h"
#include "Item.h"

class player
{
public:
    player(const std::string& texturePath, const sf::Vector2f& position);
    void move(const sf::Vector2f movement, float deltaTime);
    void takeDamage(int damage);
    void levelUp(int exp_incress);
    void Render(sf::RenderWindow& window);
    void RenderHUD(sf::RenderWindow& window);
    void initHUD();

    sf::Sprite& getSprite();
    void collectItem(Item& item);

    int getLevel();
    int getMaxHP();
    int getHP();
    int getMaxExp();
    int getExp();
    bool GetDead();


private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text levelText;
    sf::Text hpText;
    sf::Text expText;
    sf::Text Fps;


    int level;
    int max_HP, HP;
    int max_Exp, Exp;
    bool isDead = false;
    float deltatime;
};