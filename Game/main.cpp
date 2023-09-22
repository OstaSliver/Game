#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#include <math.h>
#include <SFML/System/Time.hpp>

#include "player.h"
#include "Enemy.h"
#include "Menu.h"
#include "PauseMenu.h"
#include "playerHUD.h"
#include "Map.h"
#include "circledamage.h"
#include "Item.h"
#include "FireBall.h"



#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ENEMY_SPAWN_MARGIN 0.0f

int main()
{
    restart:
   // sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game", sf::Style::Fullscreen);
   sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game");
    
    player character("Resource/sprite/character_Down.png", sf::Vector2f(9600.0f, 5400.0f));

    PauseMenu pauseMenu(window);
    PlayerHUD playerHUD(character);
    Map myMap(SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
    menu menu;


    sf::Clock clock;
    sf::Clock movementClock;
    sf::View view(sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Time cooldown;

    const sf::Time targetFrameTime = sf::seconds(1.0f / 60.0f); 
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


        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition(sf::Vector2f(sf::Mouse::getPosition(window)));

                if (menu.isPressPlayButton(mousePosition)) {
                    gameStarted = true;
                }
            }
        }

        /*if (event.type == sf::Event::MouseMoved) {

          sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

            std::cout << "Mouse Position (Window): " << mousePosition.x << ", " << mousePosition.y << std::endl;
            std::cout << "Mouse Position (World): " << worldMousePosition.x << ", " << worldMousePosition.y << std::endl;
            std::cout << "Player Position: " << character.getSprite().getPosition().x << ", " << character.getSprite().getPosition().y << std::endl;

        }*/

        if (isPause) {

            deltaTime = 0.0f;
            myMap.draw(window);

            for (auto& enemy : enemies) {
                enemy.draw(window);
            }
            for (auto it = damageCircles.begin(); it != damageCircles.end(); it++) {
                    it->draw(window);
            }
            for (auto it = item.begin(); it != item.end();it++) {
                it->draw(window);

            }


            playerHUD.draw(window);
            character.draw(window);
            pauseMenu.setPosition(character.getSprite().getPosition());
            pauseMenu.draw(window);
            window.display();
            continue;
        }

        float movementDeltaTime = movementClock.restart().asSeconds();

        if (!gameStarted) {
            window.clear();
            menu.draw(window);
            window.display();
            continue;
        }

        if (character.GetDead()) {
            goto restart;
        }

            if (enemies.size() <= 2) {
                

                int edge = std::uniform_int_distribution<int>(0, 3)(gen);

                float spawnX, spawnY;
                sf::Vector2f playerPosition = character.getSprite().getPosition();
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

            //sf::Vector2f mouseCircle = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            //std::uniform_real_distribution<float>(character.getSprite().getPosition().x - SCREEN_WIDTH / 2, character.getSprite().getPosition().x + SCREEN_WIDTH / 2)(gen);
            //sf::Vector2f posCircle(std::uniform_real_distribution<float>(character.getSprite().getPosition().x - SCREEN_WIDTH / 3, character.getSprite().getPosition().x + SCREEN_WIDTH / 3)(gen), std::uniform_real_distribution<float>(character.getSprite().getPosition().y - SCREEN_HEIGHT / 3, character.getSprite().getPosition().y + SCREEN_HEIGHT / 3)(gen));

            if (enemies.size() != 0) {
                int i = rand() % enemies.size();

                //circle dmg

                /*sf::Vector2f posCircle(enemies[i].getSprite().getPosition().x, enemies[i].getSprite().getPosition().y);
                circledamage damageCircle(100, 3.0f);
                damageCircle.drawCircle(posCircle);
                damageCircles.push_back(damageCircle);*/
                
                //fireball

                sf::Vector2f posTarget(enemies[i].getSprite().getPosition().x, enemies[i].getSprite().getPosition().y);
                sf::Vector2f posPlayer(character.getSprite().getPosition().x, character.getSprite().getPosition().y);
                FireBall fireball(posPlayer, posTarget);
                fireballs.push_back(fireball);


            }
      
            /*circledamage damageCircle(100, 3.0f);
            damageCircle.drawCircle(posCircle);
            damageCircles.push_back(damageCircle);*/

        }
        

        character.move(movement,deltaTime);


        view.setCenter(static_cast<sf::Vector2f>(character.getSprite().getPosition()));
        window.setView(view);

        sf::FloatRect playerBounds = character.getSprite().getGlobalBounds();
  
        for (size_t i = 0; i < enemies.size(); ++i) {
            enemiesPositions.push_back(enemies[i].getSprite().getPosition());
            enemies[i].moveToPlayer(character.getSprite().getPosition(), 100.0f * deltaTime);
            enemies[i].update(playerBounds);

            if (enemies[i].colWithPlayer(playerBounds)) {
                character.takeDamage(10);
                character.levelUp(20);
            }

            if (enemies[i].isDead()) {
                int rate = rand() % 100;
                if (rate <= 20) {
                    item.push_back(Item(enemies[i].getSprite().getPosition(), ItemType::EXP));
                }
                    
               
                enemies.erase(enemies.begin() + i);
                --i;
            }

        }
        window.clear();

        myMap.draw(window);
        character.draw(window);

        for (auto it = damageCircles.begin(); it != damageCircles.end();) {
            it->update(movementDeltaTime);
            if (it->isActive()) {
                it->draw(window);
                ++it;
            }
            else
            {
                it = damageCircles.erase(it);
            }
        }

        for (auto it = item.begin(); it != item.end();) {
            if (it->getPosition().getGlobalBounds().intersects(playerBounds)) {
                character.collectItem(*it);
                it = item.erase(it);
            }
            else {
                it->draw(window);
                ++it;
            }
        }

        for (auto it = fireballs.begin(); it != fireballs.end();) {
            it->updata(deltaTime);
                it->draw(window);
                ++it;
        }

        character.draw(window);

        for (auto& enemy : enemies) {

            for (auto& damageCircle : damageCircles) {
                if (damageCircle.isActive() && damageCircle.isEnemyInCircle(enemy)) {
                    enemy.takeDamage(damageCircle.getDmg());
                }
            }
            enemy.draw(window);
        }

        playerHUD.draw(window);

        window.display();
    }
}