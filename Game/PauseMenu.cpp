#include <iostream>
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window)
{
    if (!font.loadFromFile("C:/Study/CE_1/pro_fun/game/font/Pixelpoint.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    pauseText.setFont(font);
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setString("Paused");
    pauseText.setOrigin(pauseText.getGlobalBounds().width / 2, pauseText.getGlobalBounds().height / 2);

    resumeText.setFont(font);
    resumeText.setCharacterSize(30);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setString("Press 'ESC' to Resume");
    resumeText.setOrigin(pauseText.getGlobalBounds().width / 2, pauseText.getGlobalBounds().height / 2);

}

void PauseMenu::setPosition(const sf::Vector2f& playerPos)
{
    float xOffset = 0.0f; 
    float yOffset = 500.0f;  

    pauseText.setPosition(playerPos.x - xOffset, playerPos.y - yOffset);
    resumeText.setPosition(playerPos.x - xOffset-70, playerPos.y - yOffset+100);
}

void PauseMenu::draw(sf::RenderWindow& window)
{
    window.draw(pauseText);
    window.draw(resumeText);
}
