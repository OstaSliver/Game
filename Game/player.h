#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "player.h"
#include "Item.h"
#include "Ability.h"

class player
{
public:
    player(const std::string& texturePath, const sf::Vector2f& position, Ability *abilit);
    void move(const sf::Vector2f movement, float deltaTime);
    void takeDamage(int damage);
    void ExpUp(int exp_incress);
    void updateScore(int score);
    void Render(sf::RenderWindow& window);
    void RenderHUD(sf::RenderWindow& window);

    sf::Sprite& getSprite();
    bool isLevelUp = false;

    void collectItem(Item& item);

    int getLevel();
    int getMaxHP();
    int getHP();
    int getMaxExp();
    int getExp();
    int getScore();
    float getTimer();
    bool GetDead();
    bool GetLevelUp();

private:
    sf::Texture texture;
    sf::Texture AbilityTextureSpace;
    sf::Sprite AbilitySpace[3];

    Ability *ability;
    sf::Texture AbilityTexture[3];
    sf::Sprite AbilitySprite[3];

    sf::Sprite sprite;
    sf::Font font;
    sf::Text levelText;
    sf::Text hpText;
    sf::Text expText;
    sf::Text AbilityText[3];
    sf::Text TimerText;

    sf::Text Fps;
    sf::Text Score;

    sf::RectangleShape hpBar,hpBarBack;
    sf::RectangleShape expBar,expBarBack;

    int level;
    int max_HP, HP;
    int max_Exp, Exp;
    int score = 0;
    bool isDead = false;
    float deltatime;
    float Timer = 0;


    void initAbilitySpace();
    void initAbility();
    void initHUD();
    void initHPBar();
    void initExpBar();
    void initScore();
    void initTimer();
};