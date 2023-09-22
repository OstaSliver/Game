#include <iostream>
#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(player& playerObj) : playerObj(playerObj) {
    if (!font.loadFromFile("Resource/font/Pixelpoint.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
        return;
    }

    levelText.setFont(font);
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::White);

    hpText.setFont(font);
    hpText.setCharacterSize(30);
    hpText.setFillColor(sf::Color::White);

    expText.setFont(font);
    expText.setCharacterSize(30);
    expText.setFillColor(sf::Color::White);
}

void PlayerHUD::draw(sf::RenderWindow& window) {

    sf::Vector2f playerPos = playerObj.getSprite().getPosition();
    levelText.setString("Level: " + std::to_string(playerObj.getLevel()));
    hpText.setString("HP: " + std::to_string(playerObj.getHP()) + " / " + std::to_string(playerObj.getMaxHP()));
    expText.setString("EXP: " + std::to_string(playerObj.getExp()) + " / " + std::to_string(playerObj.getMaxExp()));

    levelText.setPosition(playerPos.x - 900.0f, playerPos.y - 500.0f);
    hpText.setPosition(playerPos.x - 900.0f, playerPos.y - 470.0f);
    expText.setPosition(playerPos.x - 900.0f, playerPos.y - 440.0f);

    window.draw(levelText);
    window.draw(hpText);
    window.draw(expText);
}
