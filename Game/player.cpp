#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Item.h"

player::player(const std::string& texturePath, const sf::Vector2f& position) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading player texture: " << texturePath << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(0.3f,0.3f);
    //sprite.setScale(4.f,4.f);

    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    level = 1;
    max_HP = 100;
    HP = max_HP;
    max_Exp = 100;
    Exp = 0;
    initHUD();

}

void player::move(sf::Vector2f movement, float deltaTime) {
    float speedmove = 200.0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speedmove * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speedmove * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.setScale(0.3f, 0.3f);
        movement.x += speedmove * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.setScale(-0.3f, 0.3f);
        movement.x -= speedmove * deltaTime;
    }
    this->deltatime = deltaTime;
    this->sprite.move(movement);
}




sf::Sprite &player::getSprite() {
    return sprite;
}

void player::collectItem(Item& item) {
    if (item.getType() == ItemType::EXP) {
        levelUp(50);
    }
    if (item.getType() == ItemType::HP) {
		HP += 50;
        if (HP > max_HP) {
			HP = max_HP;
		}
	}
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
        max_Exp = (level*750);
    }
}

void player::Render(sf::RenderWindow& window)
{
    RenderHUD(window);
    window.draw(sprite);

}

void player::RenderHUD(sf::RenderWindow& window)
{
    sf::Vector2f playerPos = sprite.getPosition();
	levelText.setString("Level: " + std::to_string(getLevel()));
	hpText.setString("HP: " + std::to_string(getHP()) + " / " + std::to_string(getMaxHP()));
	expText.setString("EXP: " + std::to_string(getExp()) + " / " + std::to_string(getMaxExp()));
	Fps.setString("FPS: " + std::to_string(1.0f / deltatime));

	levelText.setPosition(playerPos.x - 900.0f, playerPos.y - 500.0f);
	hpText.setPosition(playerPos.x - 900.0f, playerPos.y - 470.0f);
	expText.setPosition(playerPos.x - 900.0f, playerPos.y - 440.0f);
	Fps.setPosition(playerPos.x - 900.0f, playerPos.y - 410.0f);

	window.draw(levelText);
	window.draw(hpText);
	window.draw(expText);
	window.draw(Fps);
}

void player::initHUD()
{
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

    Fps.setFont(font);
    Fps.setCharacterSize(30);
    Fps.setFillColor(sf::Color::White);

}
