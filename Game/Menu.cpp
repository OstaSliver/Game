#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

menu::menu() {
    
        if (!font.loadFromFile("Resource/font/Pixelpoint.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
        }

        play_button.setSize(sf::Vector2f(200.0f, 50.0f));
        play_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 - 25.0f);
        play_button.setFillColor(sf::Color::Red);

        playText.setFont(font);
        playText.setString("Play");
        playText.setCharacterSize(40);
        playText.setFillColor(sf::Color::White);
        playText.setPosition(play_button.getPosition().x + 60.0f, play_button.getPosition().y - 3.0f);
  
}
void menu::draw(sf::RenderWindow& window) {
    window.draw(play_button);
    window.draw(playText);
}

bool menu::isPressPlayButton(sf::Vector2f mousePosition) {
	return play_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

