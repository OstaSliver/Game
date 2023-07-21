#include <SFML/Graphics.hpp>
#include <iostream>

#include "player.h"

player::player(const std::string& texturePath, const sf::Vector2f& position) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading player texture: " << texturePath << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(0.3f,0.3f);
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    level = 1;
    max_HP = 100;
    HP = max_HP;
    max_Exp = 100;
    Exp = 0;

}

void player::move(const sf::Vector2f& val) {
    sprite.move(val);
}

void player::setTexture(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading player texture: " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
}

void player::draw(sf::RenderWindow& window) {
    window.draw(sprite);

    sf::Font font;
    if (!font.loadFromFile("C:/Study/CE_1/pro_fun/game/font/Pixelpoint.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
        return;
    }

    sf::Text levelText("Level: " + std::to_string(level), font, 30);
    sf::Text hpText("HP: " + std::to_string(HP) + " / " + std::to_string(max_HP), font, 30);
    sf::Text expText("EXP: " + std::to_string(Exp) + " / " + std::to_string(max_Exp), font, 30);

    levelText.setPosition(10.0f, 10.0f);
    hpText.setPosition(10.0f, 40.0f);
    expText.setPosition(10.0f, 70.0f);

    window.draw(levelText);
    window.draw(hpText);
    window.draw(expText);
}

sf::Sprite &player::getSprite() {
    return sprite;
}
int player::getMaxHP() {
    return max_HP;
}

int player::getHP() {
    return HP;
}

void player::takeDamage(int damage) {
    HP -= damage;

    if (HP <= 0) {
 
    }
}

void player::levelUp(int exp_incress){
    Exp += exp_incress;
    if (Exp >= max_Exp) {
        level++;
        max_HP += 20;
        HP = max_HP;
        Exp -= max_Exp;
        max_Exp = (level*100);
    }
}