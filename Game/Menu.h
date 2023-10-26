#pragma once
#include <SFML/Graphics.hpp>	

class menu
{
public:
	menu();

	~menu();
	int selectedButtonIndex;

	void draw(sf::RenderWindow& window);

	void init();

	bool isPressPlayButton(sf::Vector2f mosuePos);
	bool isPressScoreButton(sf::Vector2f mosuePos);
	bool isPressCreditButton(sf::Vector2f mosuePos);
	bool isPressQuitButton(sf::Vector2f mosuePos);

	void isHoverPlayButton(sf::Vector2f mosuePos);
	void isHoverScoreButton(sf::Vector2f mosuePos);
	void isHoverCreditButton(sf::Vector2f mosuePos);
	void isHoverQuitButton(sf::Vector2f mosuePos);

	void moveUp();
	void moveDown();

private:
	sf::Text playText;
	sf::Text ScoreText;
	sf::Text CreditText;
	sf::Text quitText;
	sf::Text titleText;

	sf::Sprite background;
	sf::Texture textureBg;

	sf::Font font;
	sf::Font titleFont;

	sf::RectangleShape play_button;
	sf::RectangleShape score_button;
	sf::RectangleShape credit_button;
	sf::RectangleShape quit_button;

};