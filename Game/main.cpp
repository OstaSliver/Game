#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "player.h"
#include "Enemy.h"
#include "Menu.h"
#include "PauseMenu.h"
#include "playerHUD.h"
#include "Map.h"


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main()
{
    //sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game" ,sf::Style::Fullscreen);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project Game");
    player character("C:/Study/CE_1/pro_fun/game/sprite/character_Down.png", sf::Vector2f(9600.0f,5400.0f));
    PauseMenu pauseMenu(window);
    PlayerHUD playerHUD(character);
    Map myMap(SCREEN_WIDTH /10, SCREEN_HEIGHT / 10);
    menu menu;


    sf::Clock clock;
    sf::Clock movementClock;
    sf::View view(sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::View pausedView; // เก็บตำแหน่ง view ขณะที่เกมถูกค้างหยุด


    bool isPause = false;
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
                        if (!isPause) {
                            movementClock.restart();
                            pausedView = window.getView();

                        }                          
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

        /*if (event.type == sf::Event::MouseMoved) {

          sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

            std::cout << "Mouse Position (Window): " << mousePosition.x << ", " << mousePosition.y << std::endl;
            std::cout << "Mouse Position (World): " << worldMousePosition.x << ", " << worldMousePosition.y << std::endl;
            std::cout << "Player Position: " << character.getSprite().getPosition().x << ", " << character.getSprite().getPosition().y << std::endl;
           
        }*/

        if (isPause) {

            pausedView = window.getView();


            deltaTime = 0.0f;
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

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!Check_space) {
                Check_space = true;
                
                    float radius = 30.0f;
                    sf::Vector2f position(sf::Vector2f(sf::Mouse::getPosition(window)));
                    sf::Vector2f worldPosition = window.mapPixelToCoords(sf::Vector2i(position), view);

                    sf::Color color(rand() % 256, rand() % 256, rand() % 256);
                    enemies.push_back(Enemy(worldPosition, radius, color));
                
            }
        }
        else {
            Check_space = false;
        }
        
        sf::Vector2f movement(0.0f, 0.0f);
        float speedmove = 200.0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= speedmove * movementDeltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += speedmove * movementDeltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            character.getSprite().setScale(0.3f, 0.3f);
            movement.x += speedmove * movementDeltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            character.getSprite().setScale(-0.3f, 0.3f);

            movement.x -= speedmove * movementDeltaTime;
        }


        character.move(movement);

        view.setCenter(static_cast<sf::Vector2f>(character.getSprite().getPosition()));
        window.setView(view);

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


        myMap.draw(window);
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }

        playerHUD.draw(window);
        character.draw(window);
        window.display();

    }

    return 0;
}
