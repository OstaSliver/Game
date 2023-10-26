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
    EnemyBounds.left += 5;
    EnemyBounds.top += 2;
    EnemyBounds.height -= 15;
    EnemyBounds.width -= 15;

}

void Enemy::update(const sf::FloatRect& playerBounds) {
   
    if (sprite.getGlobalBounds().intersects(playerBounds)) {
        dead = true;
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


    return EnemyBounds.intersects(playerBounds);
}

void Enemy::colWithOtherEnemy(std::vector<Enemy>& enemies)
{
    if (enemies.size() == 0)
    {
		return;
	}
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && enemies[i].getSprite().getPosition() != sprite.getPosition())
        {
			sf::Vector2f direction = sprite.getPosition() - enemies[i].getSprite().getPosition();
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction /= length;
			sprite.move(direction * 1.5f);
		}
	}
}


bool Enemy::isDead(){

    return dead;
}

void Enemy::draw(sf::RenderWindow& window) {
    sprite.setTexture(texture);
    window.draw(sprite);
}



void Enemy::drawHp(sf::RenderWindow& window)
{

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