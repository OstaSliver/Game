#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


#include "FireBall.h"
#include "Enemy.h"
#include "Collision.h"

#define M_PI 3.14

FireBall::FireBall(sf::Vector2f& position, sf::Vector2f target) {
	this->Target = target;
	this->direction = this->Target - position;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	this->direction /= length;


	float rotation = atan2(direction.y, direction.x) * 180 / M_PI;

	sprite.setRotation(rotation);

	Collision::createTextureAndBitmask(texture[0],"Resource/sprite/Skill/FireBall/FB001.png");
	Collision::createTextureAndBitmask(texture[1],"Resource/sprite/Skill/FireBall/FB002.png");
	Collision::createTextureAndBitmask(texture[2],"Resource/sprite/Skill/FireBall/FB003.png");
	Collision::createTextureAndBitmask(texture[3],"Resource/sprite/Skill/FireBall/FB004.png");
	Collision::createTextureAndBitmask(texture[4],"Resource/sprite/Skill/FireBall/FB005.png");

	/*if (!texture[0].loadFromFile("Resource/sprite/Skill/FireBall/FB001.png")) {
		return;
	}
	if (!texture[1].loadFromFile("Resource/sprite/Skill/FireBall/FB002.png")) {
		return;
	}
	if (!texture[2].loadFromFile("Resource/sprite/Skill/FireBall/FB003.png")) {
		return;
	}
	if (!texture[3].loadFromFile("Resource/sprite/Skill/FireBall/FB004.png")) {
		return;
	}
	if (!texture[4].loadFromFile("Resource/sprite/Skill/FireBall/FB005.png")) {
		return;
	}
	*/
	
	sprite.setScale(1,1);
	sprite.setOrigin(texture[0].getSize().x / 2, texture[0].getSize().y / 2);

	sprite.setPosition(position);
	
}
void FireBall::update(float& deltaTime)
{
	time += deltaTime;


	if (time >= 1.0f / 15.0f) {
		time -= 1.0f / 15.0f;
		Animation = (Animation + 1) % 5;
	}
		sprite.setTexture(texture[Animation]);
		sprite.move(this->direction * 200.f * deltaTime);
	
}

void FireBall::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}


bool FireBall::isOutOfScreen(float screenWidth, float screenHeight,sf::Vector2f playerPosition){
	sf::Vector2f position = sprite.getPosition();

	return (position.x < playerPosition.x - screenWidth / 2 || position.x > playerPosition.x + screenWidth / 2 || position.y < playerPosition.y - screenHeight / 2 || position.y > playerPosition.y + screenHeight / 2);

}

bool FireBall::checkCollisionWithEnemie(std::vector<Enemy>& enemies) {

	for (Enemy& enemy : enemies) {
		 /*if(Collision::pixelPerfectTest(enemy.getSprite(), sprite) && enemies.size() > 0) {
			enemy.takeDamage(100);
			return true;
		}*/

		if (enemy.getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds())) {
			enemy.takeDamage(100);
			return true;
		}

	}
	return false;
}


sf::Sprite& FireBall::getSprite()
{
	return sprite;
}
