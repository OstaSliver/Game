#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

menu::menu() {
    init();
}
void menu::draw(sf::RenderWindow& window) {

    window.draw(background);
    window.draw(play_button);
    window.draw(score_button);
    window.draw(quit_button);
    window.draw(playText);
    window.draw(ScoreText);
    window.draw(quitText);
}

void menu::init()
{
    if (!font.loadFromFile("Resource/font/Pixelpoint.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    if (!textureBg.loadFromFile("Resource/sprite/bgmenu/bg.jpg")) {
		std::cerr << "Error loading background!" << std::endl;
	}
    
    

    textureBg.setSmooth(true);

    background.setTexture(textureBg);
    background.setScale(3.5f, 3.5f);


    play_button.setSize(sf::Vector2f(200.0f, 50.0f));
    play_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 - 25.0f);
    play_button.setFillColor(sf::Color::Red);

    

    score_button.setSize(sf::Vector2f(200.0f, 50.0f));
    score_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 + 50.0f);
    score_button.setFillColor(sf::Color::Red);
    
    quit_button.setSize(sf::Vector2f(200.0f, 50.0f));
    quit_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 + 125.0f);
    quit_button.setFillColor(sf::Color::Red);

    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(40);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(play_button.getPosition().x + 60.0f, play_button.getPosition().y - 3.0f);
    
    ScoreText.setFont(font);
    ScoreText.setString("Score");
    ScoreText.setCharacterSize(40);
    ScoreText.setFillColor(sf::Color::White);
    ScoreText.setPosition(score_button.getPosition().x + 60.0f, score_button.getPosition().y - 3.0f);


    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(40);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(quit_button.getPosition().x + 60.0f, quit_button.getPosition().y - 3.0f);

    

}

bool menu::isPressPlayButton(sf::Vector2f mousePosition) {
	return play_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressScoreButton(sf::Vector2f mousePosition) {
	return score_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressQuitButton(sf::Vector2f mousePosition) {
	return quit_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

void menu::isHoverPlayButton(sf::Vector2f mosuePos)
{
    if (play_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
		play_button.setFillColor(sf::Color::Green);
	}
    else {
		play_button.setFillColor(sf::Color::Red);
	}
}

void menu::isHoverScoreButton(sf::Vector2f mosuePos)
{
    if (score_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
		score_button.setFillColor(sf::Color::Green);
	}
    else {
		score_button.setFillColor(sf::Color::Red);
	}
}

void menu::isHoverQuitButton(sf::Vector2f mosuePos)
{
    if (quit_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
		quit_button.setFillColor(sf::Color::Green);
	}
    else {
		quit_button.setFillColor(sf::Color::Red);
	}
}