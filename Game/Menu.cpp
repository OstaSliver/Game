#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

menu::menu() {
    selectedButtonIndex = 0;
    init();
}
menu::~menu()
{

}
void menu::draw(sf::RenderWindow& window) {
    if (selectedButtonIndex == 0)
    {
		play_button.setFillColor(sf::Color::Green);
		score_button.setFillColor(sf::Color::Red);
		credit_button.setFillColor(sf::Color::Red);
		quit_button.setFillColor(sf::Color::Red);
	}
    else if (selectedButtonIndex == 1)
    {
		play_button.setFillColor(sf::Color::Red);
		score_button.setFillColor(sf::Color::Green);
		credit_button.setFillColor(sf::Color::Red);
		quit_button.setFillColor(sf::Color::Red);
	}
    else if (selectedButtonIndex == 2)
    {
		play_button.setFillColor(sf::Color::Red);
		score_button.setFillColor(sf::Color::Red);
		credit_button.setFillColor(sf::Color::Green);
		quit_button.setFillColor(sf::Color::Red);
	}
    else if (selectedButtonIndex == 3)
    {
		play_button.setFillColor(sf::Color::Red);
		score_button.setFillColor(sf::Color::Red);
		credit_button.setFillColor(sf::Color::Red);
		quit_button.setFillColor(sf::Color::Green);
	}
    else
    {
		play_button.setFillColor(sf::Color::Red);
		score_button.setFillColor(sf::Color::Red);
		credit_button.setFillColor(sf::Color::Red);
		quit_button.setFillColor(sf::Color::Red);
	}
    window.draw(background);
    window.draw(play_button);
    window.draw(score_button);
    window.draw(credit_button);
    window.draw(quit_button);
    window.draw(playText);
    window.draw(ScoreText);
    window.draw(CreditText);
    window.draw(quitText);
    window.draw(titleText);
}

void menu::init()
{
    if (!font.loadFromFile("Resource/font/monsterhunter.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    if (!titleFont.loadFromFile("Resource/font/Super Boys.ttf")) {
		std::cerr << "Error loading font!" << std::endl;
	}
    if (!textureBg.loadFromFile("Resource/sprite/bgmenu/bg.jpg")) {
		std::cerr << "Error loading background!" << std::endl;
	}
    
    

    textureBg.setSmooth(true);

    background.setTexture(textureBg);


    play_button.setSize(sf::Vector2f(200.0f, 50.0f));
    play_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 - 25.0f);
    play_button.setFillColor(sf::Color::Red);

    

    score_button.setSize(sf::Vector2f(200.0f, 50.0f));
    score_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 + 50.0f);
    score_button.setFillColor(sf::Color::Red);
    


    credit_button.setSize(sf::Vector2f(200.0f, 50.0f));
    credit_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 + 125.0f);
    credit_button.setFillColor(sf::Color::Red);


    quit_button.setSize(sf::Vector2f(200.0f, 50.0f));
    quit_button.setPosition(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 + 200.0f);
    quit_button.setFillColor(sf::Color::Red);

    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(40);
    playText.setFillColor(sf::Color::White);    
    playText.setOrigin(playText.getGlobalBounds().width / 2, playText.getGlobalBounds().height / 2);
    playText.setPosition(play_button.getPosition().x + 100.0f, play_button.getPosition().y + 10.0f);


    ScoreText.setFont(font);
    ScoreText.setString("Score");
    ScoreText.setCharacterSize(40);
    ScoreText.setFillColor(sf::Color::White);
    ScoreText.setOrigin(ScoreText.getGlobalBounds().width / 2, ScoreText.getGlobalBounds().height / 2);
    ScoreText.setPosition(score_button.getPosition().x + 100.0f, score_button.getPosition().y + 10.0f);

    CreditText.setFont(font);
    CreditText.setString("Credit");
    CreditText.setCharacterSize(40);
    CreditText.setFillColor(sf::Color::White);
    CreditText.setOrigin(CreditText.getGlobalBounds().width / 2, CreditText.getGlobalBounds().height / 2);
    CreditText.setPosition(credit_button.getPosition().x + 100.0f, credit_button.getPosition().y + 10.0f);


    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(40);
    quitText.setFillColor(sf::Color::White);
    quitText.setOrigin(quitText.getGlobalBounds().width / 2, quitText.getGlobalBounds().height / 2);
    quitText.setPosition(quit_button.getPosition().x + 100.0f, quit_button.getPosition().y + 10.0f);

    titleText.setFont(titleFont);
    titleText.setString("The Last Survivor");
    titleText.setCharacterSize(150);
    titleText.setFillColor(sf::Color::Color(255,128, 0, 255));
    titleText.setOrigin(titleText.getGlobalBounds().width / 2, titleText.getGlobalBounds().height / 2);
    titleText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300.0f);

}

bool menu::isPressPlayButton(sf::Vector2f mousePosition) {
	return play_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressScoreButton(sf::Vector2f mousePosition) {
	return score_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

bool menu::isPressCreditButton(sf::Vector2f mosuePos)
{
    return credit_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos));;
}

bool menu::isPressQuitButton(sf::Vector2f mousePosition) {
	return quit_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));;
}

void menu::isHoverPlayButton(sf::Vector2f mosuePos)
{
    if (play_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
        selectedButtonIndex = 0;
    }
}

void menu::isHoverScoreButton(sf::Vector2f mosuePos)
{
    if (score_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
        selectedButtonIndex = 1;
    }
}

void menu::isHoverCreditButton(sf::Vector2f mosuePos)
{
    if (credit_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
		selectedButtonIndex = 2;
	}
}

void menu::isHoverQuitButton(sf::Vector2f mosuePos)
{

    if (quit_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
        selectedButtonIndex = 3;
    }
}

void menu::moveUp()
{
    if (selectedButtonIndex >= 0)
    {
		selectedButtonIndex--;
	}

    if (selectedButtonIndex == -1)
    {
		selectedButtonIndex = 3;
	}
}

void menu::moveDown()
{
    if (selectedButtonIndex <= 3)
    {
		selectedButtonIndex++;
	}
    
    if (selectedButtonIndex > 3)
    {
        selectedButtonIndex = 0;
    }
}