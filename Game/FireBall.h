#pragma once
class FireBall
{
public:
	FireBall(sf::Vector2f &position, sf::Vector2f target);
	void updata(float& deltaTime);
	void draw(sf::RenderWindow& window);
private:
	sf::Vector2f Target;

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f direction;

	float elaped = 0.0;
	int Animation = 0;
};

