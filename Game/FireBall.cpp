#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


#include "FireBall.h"

#define M_PI 3.14

FireBall::FireBall(sf::Vector2f& position, sf::Vector2f target) {
	this->Target = target;
	this->direction = this->Target - position;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	this->direction /= length;


	float rotation = atan2(direction.y, direction.x) * 180 / M_PI;

	sprite.setRotation(rotation);

	if (!texture[0].loadFromFile("Resource/sprite/Skill/FireBall/FB001.png")) {
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

	
	sprite.setScale(2,2);
	sprite.setOrigin(texture[0].getSize().x / 2, texture[0].getSize().y / 2);

	sprite.setPosition(position);

	elaped = 0.0f;
	
}
void FireBall::updata(float& deltaTime)
{
	elaped += deltaTime;
	if (1/15.0f < elaped) {
		elaped = 0.0f;
		switch (this->Animation)
		{
		case 0:
			this->Animation = 1;
			break;

		case 1:
			this->Animation = 2;
			break;

		case 2:
			this->Animation = 3;
			break;

		case 3:
			this->Animation = 4;
			break;

		case 4:
			this->Animation = 0;
			break;

		default:
			break;
		}
	}
	sprite.setTexture(texture[Animation]);
	sprite.move(this->direction * 200.f * deltaTime);
}

void FireBall::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
