#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Graphics.hpp>

class PauseMenu {
public:
    PauseMenu(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text pauseText;
    sf::Text resumeText;
};

#endif // PAUSEMENU_H
