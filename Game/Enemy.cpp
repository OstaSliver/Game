#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"

Enemy::Enemy(const sf::Vector2f& position)
    : maxHP(100), currentHP(100), dead(false)
{

    if (!texture.loadFromFile("Resource/monster/slime.png")){
        std::cerr << "Error loading font file" << std::endl;
        return;
    }
    sprite.setScale(1,1);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(position);

}

void Enemy::update(const sf::FloatRect& playerBounds) {
   
    if (sprite.getGlobalBounds().intersects(playerBounds)) {
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
    return sprite.getGlobalBounds().intersects(playerBounds);
}

bool Enemy::isDead()  {
    return dead;
}

void Enemy::draw(sf::RenderWindow& window) {
    sprite.setTexture(texture);
    window.draw(sprite);
}

void Enemy::moveToPlayer(const sf::Vector2f& playerPosition, float speed) {

    sf::Vector2f direction = playerPosition - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;

    sprite.move(direction * speed);
}