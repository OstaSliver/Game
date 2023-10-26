#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Item.h"
#include "Ability.h"

player::player(const std::string& texturePath, const sf::Vector2f& position, Ability* ability) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading player texture: " << texturePath << std::endl;
    }
    this->ability = ability;

    sprite.setTexture(texture);
    sprite.setScale(0.3f, 0.3f);
    //sprite.setScale(4.f,4.f);

    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    level = 1;
    max_HP = 100;
    HP = max_HP;
    max_Exp = 5;
    Exp = 0;
    score = 0;

    initAbilitySpace();
    initAbility();
    initHUD();
    initHPBar();
    initExpBar();
    initScore();
    initTimer();

}

void player::move(sf::Vector2f movement, float deltaTime) {
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
    if (sf::Joystick::isConnected(0)) {
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        if (x > 20.0f || x < -20.0f || y < -20.0f || y > 20.0f) {
            sf::Vector2f direction(x, y);
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;
            movement = direction * speedmove * deltaTime;
        }

    }
    this->Timer += deltaTime;
    this->deltatime = deltaTime;
    this->sprite.move(movement);
}




sf::Sprite &player::getSprite() {
    return sprite;
}

void player::collectItem(Item& item) {
    if (item.getType() == ItemType::EXP) {
        ExpUp(1);
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

int player::getScore()
{
    return this->score;
}

float player::getTimer()
{
    return Timer;
}

bool player::GetDead(){
    return isDead;
}

bool player::GetLevelUp()
{
    return isLevelUp;
}

void player::takeDamage(int damage) {
    HP -= damage;

    if (HP <= 0) {
        this->isDead = true;
    }
}

void player::ExpUp(int exp_incress){
    Exp += exp_incress;
    if (Exp >= max_Exp) {
        level++;
        max_HP += 20;
        HP = max_HP;
        Exp -= max_Exp;
        max_Exp += 10;
        isLevelUp = true;
    }
}

void player::updateScore(int score)
{
    this->score += score;
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

	levelText.setPosition(playerPos.x + 700.0f, playerPos.y - 500.0f);
	hpText.setPosition(playerPos.x + 700.0f, playerPos.y - 470.0f);

	expText.setPosition(playerPos.x + 700.0f, playerPos.y - 440.0f);
	Fps.setPosition(playerPos.x + 700.0f, playerPos.y - 410.0f);

    hpBar.setPosition(playerPos.x - 50.0f, playerPos.y + 45.0f);
	hpBar.setSize(sf::Vector2f(((float)HP/(float)max_HP)*100.0f, 10.0f));
    hpBarBack.setPosition(playerPos.x - 50.0f, playerPos.y + 45.0f);

    expBar.setPosition(playerPos.x - 990, playerPos.y - 540.0f);
    expBar.setSize(sf::Vector2f(((float)Exp/(float)max_Exp)*expBarBack.getSize().x, 30.0f));
    expBarBack.setPosition(playerPos.x -990, playerPos.y - 540);

    Score.setString("Score: " + std::to_string(this->score));
    Score.setPosition(playerPos.x + 100.0f, playerPos.y - 480.0f);

    TimerText.setString(std::to_string((int)Timer /60 )+ ":" + std::to_string((int)Timer % 60));

    TimerText.setPosition(playerPos.x-50.0f, playerPos.y - 500.0f);

    for (int i = 0; i < 3; i++) {
		AbilitySpace[i].setPosition(playerPos.x - 960.0f + (60*i), playerPos.y - 500.0f);
	}

    AbilitySprite[0].setPosition(playerPos.x - 950.0f, playerPos.y - 490.0f);
    AbilitySprite[1].setPosition(playerPos.x - 890.0f, playerPos.y - 490.0f);

    for (int i = 0; i < 3; i++) {
        window.draw(AbilitySpace[i]);
        window.draw(AbilitySprite[i]);

   	}

    window.draw(hpBarBack);
    window.draw(hpBar);
    window.draw(expBarBack);
    window.draw(expBar);
	window.draw(levelText);
	window.draw(hpText);
	window.draw(expText);
    window.draw(Score);
	window.draw(Fps);
    window.draw(TimerText);
}


void player::initAbilitySpace()
{
    if (!AbilityTextureSpace.loadFromFile("Resource/sprite/item/BoxAbility.png")) {
		std::cerr << "Error loading Ability texture: " << std::endl;
	}
    for (int i = 0; i < 3; i++) {
        AbilitySpace[i].setTexture(AbilityTextureSpace);
		AbilitySpace[i].setScale(0.3f,0.3f);
		AbilitySpace[i].setPosition(sprite.getPosition().x - 100.0f - (30*i), sprite.getPosition().y - 100.0f);
    }

}

void player::initAbility()
{
    for (int i = 0; i < 3; i++) {

        if (AbilityType::FireBall == ability[i].getType()) {
            AbilityTexture[i].loadFromFile("Resource/sprite/Item/FireBallAbility.png");
            AbilitySprite[i].setTexture(AbilityTexture[i]);
            AbilitySprite[i].setScale(0.4f, 0.4f);
        }
        if (AbilityType::CircleDamage == ability[i].getType()) {
			AbilityTexture[i].loadFromFile("Resource/sprite/Item/Circle.png");
			AbilitySprite[i].setTexture(AbilityTexture[i]);
			AbilitySprite[i].setScale(0.4f, 0.4f);
		}
	}
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

void player::initHPBar()
{
    hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(sf::Vector2f(100.0f, 10.0f));

	hpBarBack.setFillColor(sf::Color::Black);
    hpBarBack.setSize(sf::Vector2f(100.0f, 10.0f));


}

void player::initExpBar()
{
    expBar.setFillColor(sf::Color::Yellow);
	expBar.setSize(sf::Vector2f(1980.0f, 30.0f));

    expBarBack.setFillColor(sf::Color::Black);
    expBarBack.setSize(sf::Vector2f(1980.0f, 30.0f));
}

void player::initScore()
{
    Score.setFont(font);
	Score.setCharacterSize(30);
	Score.setFillColor(sf::Color::White);

}

void player::initTimer()
{
    Timer = 0.0f;
    TimerText.setFont(font);
    TimerText.setCharacterSize(60);
    TimerText.setFillColor(sf::Color::White);
}
