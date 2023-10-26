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
	float Hitboxdelay;
	float Hitboxelapsed;
	std::vector <Enemy> enemyInCircle;
	int damageCircle;
	bool active;
	bool Hitboxactive;

public:
	circledamage(sf::Vector2f pos ,int radius,float duration,float Hitboxdelay);
	void draw(sf::RenderWindow& window);
	bool isEnemyInCircle(Enemy enemy);
	void takeDamageinCircle(std::vector<Enemy>& enemise);
	bool isHitboxDelayOver();
	bool isActive();
	int getDmg();
	void update(float& deltaTime);
	void drawCircle(sf::Vector2f& pos);

};