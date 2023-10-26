#include <SFML/Graphics.hpp>
#include <math.h>
#include "circledamage.h"
#include <iostream>

circledamage::circledamage(sf::Vector2f pos,int radius, float duration,float Hitboxdelay) {
	circle.setRadius(100);
	circle.setFillColor(sf::Color::Color(0, 0, 255, 100));
	circle.setOrigin(100, 100);
	circle.setPosition(pos);
	damageCircle = 100;;
	this->duration = duration;
	this->Hitboxdelay = Hitboxdelay;
	elapsed = 0.0f;
	active = true;
}

void circledamage::draw(sf::RenderWindow& window) {
		window.draw(circle);
}


bool circledamage::isEnemyInCircle(Enemy enemy) {
	
	sf::Vector2f enemy_position = enemy.getSprite().getPosition();
	float distanec = std::sqrt(pow(enemy_position.x - circle.getPosition().x, 2) + pow(enemy_position.y - circle.getPosition().y, 2));

	return distanec <= circle.getRadius();
}

void circledamage::takeDamageinCircle(std::vector<Enemy>& enemise)
{
	if(!Hitboxactive) return;
	for (int i = 0; i < enemise.size(); i++) {
		if (isEnemyInCircle(enemise[i])) {
			enemise[i].takeDamage(damageCircle);
		}
	}
	Hitboxactive = false;
}

bool circledamage::isHitboxDelayOver()
{
	return Hitboxactive;
}

void circledamage::drawCircle(sf::Vector2f& pos) {
	circle.setPosition(pos);
	active = true;
	elapsed = 0.0f;
}

bool circledamage::isActive() {
	return active;
}

void circledamage::update(float& deltaTime) {
	if (active) {
		elapsed += deltaTime;
		Hitboxelapsed += deltaTime;
		if (elapsed >= duration) {
			active = false;
		}
		if (Hitboxelapsed >= Hitboxdelay) {
			Hitboxactive = true;
			Hitboxelapsed -= Hitboxdelay;

		}
	}
}