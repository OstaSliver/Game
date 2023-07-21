#include <SFML/Graphics.hpp>
#include "PauseMenu.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

PauseMenu::PauseMenu(sf::RenderWindow& windowt)
{
    if (!font.loadFromFile("C:/Study/CE_1/pro_fun/game/font/Pixelpoint.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    pauseText.setFont(font);
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setString("Paused");
    pauseText.setPosition(SCREEN_WIDTH / 2 - pauseText.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - 60);

    instructionText.setFont(font);
    instructionText.setCharacterSize(30);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setString("Press 'ESC' to Resume\n");
    instructionText.setPosition(SCREEN_WIDTH / 2 - instructionText.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 + 30);
}

void PauseMenu::draw(sf::RenderWindow &window)
{
    window.draw(pauseText);
    window.draw(instructionText);
}