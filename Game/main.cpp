﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <SFML/System/Time.hpp>
#include <memory>

#include "player.h"
#include "Enemy.h"
#include "Menu.h"
#include "PauseMenu.h"
#include "Map.h"
#include "circledamage.h"
#include "Item.h"
#include "FireBall.h"
#include "Ability.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ENEMY_SPAWN_MARGIN 0.0f

int main()
{
restart:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game");
    window.setFramerateLimit(30);

    Ability ability[3] = {
        {1.5f, AbilityType::FireBall},
        {0.0f, AbilityType::None},
        {0.0f, AbilityType::None}
    };

    std::unique_ptr<player> character = std::make_unique<player>("Resource/sprite/character_Down.png", sf::Vector2f(9600.0f, 5400.0f), ability);

    PauseMenu pauseMenu(window);
    Map myMap(SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
    menu menu;

    sf::Clock clock;
    sf::Clock movementClock;
    sf::View view(sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Time cooldown;

    const sf::Time targetFrameTime = sf::seconds(1.0f / 30.0f);

    sf::Clock frameClock;

    bool gameStarted = false;
    bool Check_space = false;
    bool isPause = false;
    float deltaTime = 0.0f;

    std::vector<Enemy> enemies;
    std::vector<sf::Vector2f> enemiesPositions;
    std::vector<circledamage> damageCircles;
    std::vector<Item> item;
    std::vector<FireBall> fireballs;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (gameStarted) {
                        isPause = !isPause;
                        if (!isPause) {
                            movementClock.restart();
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::M) {
                    goto restart;
                }
            }
        }

        deltaTime = clock.restart().asSeconds();
        cooldown.asSeconds();

        sf::Time elapsed = frameClock.restart();

        if (elapsed < targetFrameTime)
        {
            sf::sleep(targetFrameTime - elapsed);
            elapsed = targetFrameTime;
        }

        if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
            menu.isHoverPlayButton(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            menu.isHoverScoreButton(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            menu.isHoverQuitButton(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition(sf::Vector2f(sf::Mouse::getPosition(window)));

                if (menu.isPressPlayButton(mousePosition)) {
                    gameStarted = true;
                }
                if (menu.isPressScoreButton(mousePosition)) {
                    std::cout << "Score" << std::endl;
                }
                if (menu.isPressQuitButton(mousePosition)) {
                    window.close();
                }
            }
        }

        float movementDeltaTime = movementClock.restart().asSeconds();

        if (!gameStarted) {
            window.clear();
            menu.draw(window);
            window.display();
            continue;
        }

        if (isPause) {
            deltaTime = 0.0f;
            myMap.draw(window);

            for (auto& enemy : enemies) {
                enemy.draw(window);
            }
            for (auto it = damageCircles.begin(); it != damageCircles.end(); it++) {
                it->draw(window);
            }
            for (auto it = item.begin(); it != item.end(); it++) {
                it->draw(window);
            }

            character->Render(window);

            pauseMenu.setPosition(character->getSprite().getPosition());
            pauseMenu.draw(window);
            window.display();
            continue;
        }

        if (character->GetDead()) {
            goto restart;
        }

        if (enemies.size() <= 40) {
            int edge = std::uniform_int_distribution<int>(0, 3)(gen);

            float spawnX, spawnY;
            sf::Vector2f playerPosition = character->getSprite().getPosition();
            switch (edge) {
            case 0: // Top
                spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                spawnY = (playerPosition.y - SCREEN_HEIGHT / 2 - ENEMY_SPAWN_MARGIN) - 60;
                break;
            case 1: // Right
                spawnX = playerPosition.x + SCREEN_WIDTH / 2 + ENEMY_SPAWN_MARGIN;
                spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                break;
            case 2: // Bottom
                spawnX = std::uniform_real_distribution<float>(playerPosition.x - SCREEN_WIDTH / 2, playerPosition.x + SCREEN_WIDTH / 2)(gen);
                spawnY = playerPosition.y + SCREEN_HEIGHT / 2 + ENEMY_SPAWN_MARGIN;
                break;
            case 3: // Left
                spawnX = (playerPosition.x - SCREEN_WIDTH / 2 - ENEMY_SPAWN_MARGIN) - 60;
                spawnY = std::uniform_real_distribution<float>(playerPosition.y - SCREEN_HEIGHT / 2, playerPosition.y + SCREEN_HEIGHT / 2)(gen);
                break;
            default:
                break;
            }

            sf::Vector2f spawnPosition(spawnX, spawnY);
            enemies.push_back(Enemy(spawnPosition));
        }

        sf::Vector2f movement(0.0f, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            if (enemies.size() > 0) {
                int i = rand() % enemies.size();

                std::uniform_real_distribution<float> distX(enemies[i].getSprite().getPosition().x - SCREEN_WIDTH / 2, enemies[i].getSprite().getPosition().x + SCREEN_WIDTH / 2);
                std::uniform_real_distribution<float> distY(enemies[i].getSprite().getPosition().y - SCREEN_HEIGHT / 2, enemies[i].getSprite().getPosition().y + SCREEN_HEIGHT / 2);

                sf::Vector2f posTarget(distX(gen), distY(gen));
                sf::Vector2f posPlayer(character->getSprite().getPosition().x, character->getSprite().getPosition().y);
                FireBall fireball(posPlayer, posTarget);
                fireballs.push_back(fireball);
            }
        }

        if (ability[0].canUse()) {
            for (int i = 0; i < 1; i++) {
                if (enemies.size() > 0) {
                    int randomIndex = rand() % enemies.size();
                    sf::Vector2f enemyPosition = enemies[randomIndex].getSprite().getPosition();

                    sf::Vector2f distFromCenter;
                    distFromCenter.x = enemyPosition.x - SCREEN_WIDTH / 2;
                    distFromCenter.y = enemyPosition.y - SCREEN_HEIGHT / 2;

                    sf::Vector2f posPlayer(character->getSprite().getPosition().x, character->getSprite().getPosition().y);
                    sf::Vector2f posTarget = posPlayer + distFromCenter;

                    FireBall fireball(posPlayer, posTarget);
                    fireballs.push_back(fireball);
                }
            }
            ability[0].use();
        }

        ability[0].update(deltaTime);
        character->move(movement, deltaTime);

        view.setCenter(static_cast<sf::Vector2f>(character->getSprite().getPosition()));
        window.setView(view);
        window.clear();
        myMap.draw(window);

        sf::FloatRect playerBounds = character->getSprite().getGlobalBounds();

        for (size_t i = 0; i < enemies.size(); ++i) {
            enemiesPositions.push_back(enemies[i].getSprite().getPosition());
            enemies[i].moveToPlayer(character->getSprite().getPosition(), 200.0f * deltaTime);
            enemies[i].update(playerBounds);

            if (enemies[i].colWithPlayer(playerBounds)) {
                character->takeDamage(10);
                character->levelUp(20);
            }

            if (enemies[i].isDead()) {
                character->updateScore(1);
                int rate = rand() % 100;

                if (rate <= 3) {
                    item.push_back(Item(enemies[i].getSprite().getPosition(), ItemType::HP));
                }
                else if (20 <= rate && rate <= 30) {
                    item.push_back(Item(enemies[i].getSprite().getPosition(), ItemType::EXP));
                }
                enemies.erase(enemies.begin() + i);
                --i;
            }
        }

        for (auto it = item.begin(); it != item.end();) {
            if (it->getPosition().getGlobalBounds().intersects(playerBounds)) {
                character->collectItem(*it);
                it = item.erase(it);
            }
            else {
                it->draw(window);
                ++it;
            }
        }

        for (auto it = fireballs.begin(); it != fireballs.end();) {
            it->update(deltaTime);
            if ((it->checkCollisionWithEnemie(enemies) || it->isOutOfScreen(SCREEN_WIDTH, SCREEN_HEIGHT, character->getSprite().getPosition())) && fireballs.size() > 0) {
                it = fireballs.erase(it);
            }
            else {
                it->draw(window);
                ++it;
            }
        }

        character->Render(window);

        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
        character->Render(window);

        window.display();
    }
}