#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position);

    void update(const sf::FloatRect& playerBounds);
    void takeDamage(int damage);
    bool isDead() ;
    void draw(sf::RenderWindow& window);
    bool colWithPlayer(const sf::FloatRect& playerBounds);
    bool isOutOfScreen(float screenWidth, float screenHeight, sf::Vector2f playerPosition);
    void moveToPlayer(const sf::Vector2f& pos_Player, float speed);
    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    int maxHP;
    int currentHP;
    bool dead;
 
};