#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"

sf::Vector2f checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {

    if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds())) {

        sf::Vector2f direction = sprite2.getPosition() - sprite1.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        float offset = (sprite1.getGlobalBounds().width + sprite2.getGlobalBounds().width) * 0.7f;
        sf::Vector2f newPosition = sprite2.getPosition() + direction * offset;

        return newPosition;
    }

    return sprite1.getPosition();
}

Enemy::Enemy(const sf::Vector2f& position)
    : maxHP(100), currentHP(100), dead(false)
{

    if (!texture.loadFromFile("Resource/monster/slime.png")){
        std::cerr << "Error loading texture monster" << std::endl;
        return;
    }
    sprite.setScale(0.5,0.5);
    sprite.setOrigin(static_cast<float>(texture.getSize().x )/ 2, static_cast<float>(texture.getSize().y / 2));
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

bool Enemy::colWithPlayer(const sf::FloatRect& playerBounds){
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

sf::Sprite& Enemy::getSprite() {
    return sprite;
}