#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

class circledamage
{
private:
	sf::CircleShape circle;
	//sf::Time duration;
	//sf::Time elapsed
	float elapsed;
	float duration;
	std::vector <Enemy> enemyInCircle;
	int damageCircle;
	bool active;

public:
	circledamage(int radius,float duration);
	void draw(sf::RenderWindow& window);
	bool isEnemyInCircle(Enemy& enemy);
	bool isActive();
	int getDmg();
	void update(float& deltaTime);
	void drawCircle(sf::Vector2f& pos);

};