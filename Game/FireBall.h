#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class FireBall
{
public:
	FireBall(sf::Vector2f& position, sf::Vector2f target);
	void update(float& deltaTime);
	void draw(sf::RenderWindow& window);
	bool isOutOfScreen(float screenWidth, float screenHeight,sf::Vector2f position);
	bool checkCollisionWithEnemie(std::vector<Enemy>& enemies);

	sf::Sprite& getSprite();
	

private:
	sf::Vector2f Target;

	sf::Sprite sprite;
	sf::Texture texture[5] = {};
	sf::Vector2f direction;

	int Animation = 0;
	float time = 0.0f;
};

