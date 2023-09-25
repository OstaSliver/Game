#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"
#include "Collision.h"

Enemy::Enemy(const sf::Vector2f& position): maxHP(100), currentHP(100), dead(false)
{
    Collision::createTextureAndBitmask(texture, "Resource/sprite/monster/slime.png");

    /*if (!texture.loadFromFile("Resource/sprite/monster/slime.png")){
        std::cerr << "Error loading texture monster" << std::endl;
        return;
    }*/

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

   
    sf::FloatRect EnemyBounds = sprite.getGlobalBounds();
    
    /*EnemyBounds.left += 5;
    EnemyBounds.top += 2;
    EnemyBounds.height -= 15;

    EnemyBounds.width -= 15;

    sf::RectangleShape boundsRect(sf::Vector2f(EnemyBounds.width, EnemyBounds.height));


    boundsRect.setOutlineColor(sf::Color::Red);
    boundsRect.setOutlineThickness(2);
    boundsRect.setFillColor(sf::Color::Transparent);
    boundsRect.setPosition(EnemyBounds.left, EnemyBounds.top);*/


    return EnemyBounds.intersects(playerBounds);
}

bool Enemy::isDead(){

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