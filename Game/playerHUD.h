#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

class PlayerHUD {
public:
    PlayerHUD(player& playerObj);

    void draw(sf::RenderWindow& window, float deltatime);


private:
    player& playerObj;
    sf::Font font;
    sf::Text levelText;
    sf::Text hpText;
    sf::Text expText;
    sf::Text Fps;
};