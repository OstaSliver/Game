#include "LevelUpGui.h"

LevelUpGui::LevelUpGui(sf::RenderWindow& window)
{
	if (!font.loadFromFile("Resource/font/Pixelpoint.ttf")) {
		std::cerr << "Error loading font!" << std::endl;
	}

	levelUpText.setFont(font);
	levelUpText.setCharacterSize(60);
	levelUpText.setFillColor(sf::Color::Black);
	levelUpText.setString("Level Up!");
	levelUpText.setOrigin(levelUpText.getGlobalBounds().width / 2, levelUpText.getGlobalBounds().height / 2);
	
	levelUpBackground.setFillColor(sf::Color::White);
	levelUpBackground.setSize(sf::Vector2f(500.0f, 600.0f));
	levelUpBackground.setOrigin(levelUpBackground.getGlobalBounds().width / 2, levelUpBackground.getGlobalBounds().height / 2);

}

void LevelUpGui::Render(sf::RenderWindow& window)
{
	window.draw(levelUpBackground);
	window.draw(levelUpText);
}

void LevelUpGui::setPosition(const sf::Vector2f& playerPos)
{
	float xOffset = 0.0f;
	float yOffset = 250.0f;

	levelUpText.setPosition(playerPos.x , playerPos.y-yOffset);
	levelUpBackground.setPosition(playerPos.x , playerPos.y );

}
