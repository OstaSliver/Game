#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "player.h"
#include "Enemy.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game" ,sf::Style::Fullscreen);
    player character("C:/Study/CE_1/pro_fun/game/sprite/character_Down.png", sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
    sf::Clock clock;

    bool Check_space = false;
    std::vector<Enemy> enemies;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        sf::Vector2f movement(0.0f, 0.0f);
        float speedmove = 200.0;
        float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!Check_space) {
                Check_space = true; // กำหนดให้ปุ่มถูกกดค้าง
                if (enemies.size() < 5) {
                    float radius = 30.0f;
                    sf::Vector2f position(sf::Vector2f(sf::Mouse::getPosition(window)));
                    sf::Color color(rand() % 256, rand() % 256, rand() % 256);
                    enemies.push_back(Enemy(position, radius, color));
                }
            }
        }
        else {
            Check_space = false; // กำหนดให้ปุ่มถูกปล่อย
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= speedmove * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += speedmove * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            character.getSprite().setScale(0.5f, 0.5f);
            movement.x += speedmove * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            character.getSprite().setScale(-0.5f, 0.5f);

            movement.x -= speedmove * deltaTime;
        }
        

        character.move(movement);

        sf::FloatRect playerBounds = character.getSprite().getGlobalBounds();

        for (int i = 0; i < enemies.size(); ++i) {
            enemies[i].moveToPlayer(character.getSprite().getPosition(), 100.0f * deltaTime);
            enemies[i].update(playerBounds);

            if (enemies[i].colWithPlayer(playerBounds)) {

                character.levelUp(20);
            }

            if (enemies[i].isDead()) {
                enemies.erase(enemies.begin() + i);
                --i;
            }
        }

        window.clear();

        for (auto& enemy : enemies) {
            enemy.draw(window);
        }

        character.draw(window);
        window.display();
    }

    return 0;
}
