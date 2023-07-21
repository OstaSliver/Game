#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "player.h"
#include "Enemy.h"
#include "Map_gen.h"
#include "Menu.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080



int main()
{
    //sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game" ,sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game");

    player character("C:/Study/CE_1/pro_fun/game/sprite/character_Down.png", sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
    Map_gen back("C:/Study/CE_1/pro_fun/game/sprite/grass.png", 100, 100);

    sf::Clock clock;

    menu menu;

    bool gameStarted = false;
    bool Check_space = false;
    bool isPause = false;
    bool showMenu = true;

    std::vector<Enemy> enemies;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    if (gameStarted) {
                        isPause = !isPause;
                        window.clear();
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition(sf::Vector2f(sf::Mouse::getPosition(window)));
                if (menu.isPressPlayButton(mousePosition)) {
                    gameStarted = true;
                    showMenu = false;
                }
            }
        }

        if (!gameStarted||showMenu) {
            window.clear();
            menu.draw(window);
            window.display();
            continue;
        }


        sf::Vector2f movement(0.0f, 0.0f);
        float speedmove = 200.0;
        float deltaTime = clock.restart().asSeconds();

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
            if (!isPause) {
                enemies[i].moveToPlayer(character.getSprite().getPosition(), 100.0f * deltaTime);
                enemies[i].update(playerBounds);
            }

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

        
        back.draw(window);
        
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }

        if (isPause) {
            window.clear();
            menu.draw(window);
            window.display();
            continue;
        }

        character.draw(window);
        window.display();

    }

    return 0;
}
