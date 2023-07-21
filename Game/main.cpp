﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "player.h"
#include "Enemy.h"
#include "Menu.h"
#include "PauseMenu.h"


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080



int main()
{
    //sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game" ,sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game");

    player character("C:/Study/CE_1/pro_fun/game/sprite/character_Down.png", sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
    PauseMenu pauseMenu(window);




    sf::Clock clock;
    menu menu;

    bool gameStarted = false;
    bool Check_space = false;
    bool isPause = false;
    float deltaTime = 0.0f;

    std::vector<Enemy> enemies;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (gameStarted) {
                        isPause = !isPause;
                    }
                }
            }
        }

        deltaTime = clock.restart().asSeconds();


        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition(sf::Vector2f(sf::Mouse::getPosition(window)));
                if (menu.isPressPlayButton(mousePosition)) {
                    gameStarted = true;
                }
            }
        }

        if (isPause) {

            deltaTime = 0.0f;
            pauseMenu.draw(window);
            window.display();
            continue;
        }


        if (!gameStarted) {
            window.clear();
            menu.draw(window);
            window.display();
            continue;
        }

        sf::Vector2f movement(0.0f, 0.0f);
        float speedmove = 200.0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!Check_space) {
                Check_space = true;
                
                    float radius = 30.0f;
                    sf::Vector2f position(sf::Vector2f(sf::Mouse::getPosition(window)));
                    sf::Color color(rand() % 256, rand() % 256, rand() % 256);
                    enemies.push_back(Enemy(position, radius, color));
                
            }
        }
        else {
            Check_space = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= speedmove * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += speedmove * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            character.getSprite().setScale(0.3f, 0.3f);
            movement.x += speedmove * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            character.getSprite().setScale(-0.3f, 0.3f);

            movement.x -= speedmove * deltaTime;
        }
        

        character.move(movement);

        sf::FloatRect playerBounds = character.getSprite().getGlobalBounds();

        for (int i = 0; i < enemies.size(); ++i) {
            
                enemies[i].moveToPlayer(character.getSprite().getPosition(), 100.0f * deltaTime);
                enemies[i].update(playerBounds);
            

            if (enemies[i].colWithPlayer(playerBounds)) {

                character.takeDamage(10);
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
