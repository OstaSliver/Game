#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"

Enemy::Enemy(const sf::Vector2f& position, float radius, const sf::Color& color)
    : maxHP(100), currentHP(100), dead(false)
{
    circle.setPosition(position);
    circle.setRadius(radius);
    circle.setFillColor(color);
}

void Enemy::update(const sf::FloatRect& playerBounds) {
   
    if (circle.getGlobalBounds().intersects(playerBounds)) {
        
        dead = true;
        //takeDamage(10);
    }
}

void Enemy::takeDamage(int damage) {
    currentHP -= damage;


    if (currentHP <= 0) {
        dead = true;
    }
}

bool Enemy::colWithPlayer(const sf::FloatRect& playerBounds)  {
    return circle.getGlobalBounds().intersects(playerBounds);
}

bool Enemy::isDead()  {
    return dead;
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(circle);
}

void Enemy::moveToPlayer(const sf::Vector2f& playerPosition, float speed) {

    sf::Vector2f direction = playerPosition - circle.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;

    circle.move(direction * speed);
}