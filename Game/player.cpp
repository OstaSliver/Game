#include <iostream>
#include <SFML/Graphics.hpp>
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


void player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Sprite &player::getSprite() {
    return sprite;
}
int player::getLevel() {
    return level;
}
int player::getMaxHP() {
    return max_HP;
}

int player::getHP() {
    return HP;
}

int player::getMaxExp() {
    return max_Exp;
}

int player::getExp() {
    return Exp;
}

bool player::GetDead(){
    return isDead;
}
void player::takeDamage(int damage) {
    HP -= damage;

    if (HP <= 0) {
        this->isDead = true;
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



