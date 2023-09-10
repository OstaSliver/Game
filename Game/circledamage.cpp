#include <SFML/Graphics.hpp>
#include <math.h>
#include "circledamage.h"


circledamage::circledamage(int radius, float duration) {
	circle.setRadius(100);
	circle.setFillColor(sf::Color::Color(255, 0, 0, 100));
	circle.setOrigin(100, 100);
	damageCircle = 100;;
	this->duration = duration;
	//elapsed = sf::Time::Zero;
	elapsed = 0.0f;
	active = false;
}

void circledamage::draw(sf::RenderWindow& window) {

	if (active) {
		window.draw(circle);
	}

}

bool circledamage::isEnemyInCircle(Enemy& enemy) {

	if (!active) {
		return false;
	}

	sf::Vector2f enemy_position = enemy.getSprite().getPosition();
	float distanec = std::sqrt(pow(enemy_position.x - circle.getPosition().x, 2) + pow(enemy_position.y - circle.getPosition().y, 2));

	return distanec <= circle.getRadius();
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
		if (elapsed >= duration) {
			active = false;
		}
	}
}

int circledamage::getDmg() {
	return damageCircle;
}