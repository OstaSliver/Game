#include <vector>
#include <random>
#include <fstream>
#include <memory>
#include <sstream>

#include "player.h"
#include "Enemy.h"
#include "Menu.h"
#include "PauseMenu.h"
#include "Map.h"
#include "circledamage.h"
#include "Item.h"
#include "FireBall.h"
#include "Ability.h"
#include "LevelUpGui.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ENEMY_SPAWN_MARGIN 0.0f


void saveScore(std::string name, int score) {
	std::ofstream file;
	file.open("Resource/scoreboard.txt", std::ios::app);
	file << name << " " << score << std::endl;
	file.close();
}

void PrintScore(sf::Text *ScoreTop)
{
    std::ifstream file;
	file.open("Resource/scoreboard.txt");
	std::string line;
	std::vector<std::pair<std::string, int>> scores;
    while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string name;
		int score;
		iss >> name >> score;
		scores.push_back(std::make_pair(name, score));
	}
	file.close();
    std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		return a.second > b.second;
		});
   
    for (int i = 0; i < 5 &&  i < scores.size() ; i++) {
        ScoreTop[i].setString("TOP " + std::to_string(i+1) + " : " + scores[i].first + " " + std::to_string(scores[i].second));
    }
    
}


int main()
{
restart:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "THE LAST SURVIVOR" , sf::Style::Fullscreen);
    window.setFramerateLimit(30);

    Ability ability[3] = {
        {1.5f, AbilityType::FireBall},
        {4.5f, AbilityType::None},
        {0.0f, AbilityType::None}
    };

    std::unique_ptr<player> character = std::make_unique<player>("Resource/sprite/character_Down.png", sf::Vector2f(9600.0f, 5400.0f), ability);

    PauseMenu pauseMenu(window);
    Map myMap(SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
    menu menu;
    //LevelUpGui levelUpGui(window,ability);

    sf::Clock clock;
    sf::Clock movementClock;
    sf::View view(sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Time cooldown;


    sf::Text ScoreTop[5];
    sf::Font font;
    font.loadFromFile("Resource/font/Super Boys.ttf");

    const sf::Time targetFrameTime = sf::seconds(1.0f / 30.0f);

    sf::Clock frameClock;

    sf::Sprite backgroundScore;
    sf::Texture textureScore;
    textureScore.loadFromFile("Resource/sprite/bgmenu/bg3.jpg");
    backgroundScore.setTexture(textureScore);

    sf::Sprite backgroundCredit;
    sf::Texture textureCredit;
    textureCredit.loadFromFile("Resource/sprite/bgmenu/bg2.jpg");
    backgroundCredit.setTexture(textureCredit);
    
    bool isMenu = true;
    bool gameStarted = false;
    bool isPause = false;
    bool enterName = false;
    bool ShowScore = false;
    bool Credit = false;

    float deltaTime = 0.0f;

    std::vector<Enemy> enemies;
    std::vector<Enemy> enemies2;

    std::vector<sf::Vector2f> enemiesPositions;
    std::vector<circledamage> damageCircles;
    std::vector<Item> item;
    std::vector<FireBall> fireballs;


    std::random_device rd;
    std::mt19937 gen(rd());

    std::string name;

    srand(time(NULL));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::GainedFocus) {
                isPause = false;
            }
            if (event.type == sf::Event::LostFocus) {
                isPause = true;
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

        if (isMenu) {
            if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {

                menu.isHoverPlayButton(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                menu.isHoverScoreButton(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                menu.isHoverCreditButton(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                menu.isHoverQuitButton(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(sf::Vector2f(sf::Mouse::getPosition(window)));

                    if (menu.isPressPlayButton(mousePosition)) {
                        enterName = true;
                    }
                    if (menu.isPressScoreButton(mousePosition)) {
                        PrintScore(ScoreTop);
                        ShowScore = true;
                    }
                    if (menu.isPressCreditButton(mousePosition)) {
                        Credit = true;
                    }
                    if (menu.isPressQuitButton(mousePosition)) {
                        window.close();
                    }
                }
            }

            if (event.key.code == sf::Keyboard::W) {
                menu.moveUp();
                sf::sleep(sf::milliseconds(200));
                event.key.code = sf::Keyboard::Unknown;
            }

            if (event.key.code == sf::Keyboard::S) {
                menu.moveDown();
                sf::sleep(sf::milliseconds(200));
                event.key.code = sf::Keyboard::Unknown;
            }

            if (event.key.code == sf::Keyboard::Enter) {
                if (menu.selectedButtonIndex == 0) {
                    enterName = true;
                }
                if (menu.selectedButtonIndex == 1) {
                    PrintScore(ScoreTop);
                    ShowScore = true;
                }
                if (menu.selectedButtonIndex == 2) {
                    Credit = true;
                }
                if (menu.selectedButtonIndex == 3) {
                    window.close();
                }
            }

            if (sf::Joystick::isConnected(0)) {
                float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                if (y > 20.0f) {
                    menu.moveDown();
                    sf::sleep(sf::milliseconds(200));
                }
                if (y < -20.0f) {
                    menu.moveUp();
                    sf::sleep(sf::milliseconds(200));
                }
                if (sf::Joystick::isButtonPressed(0, 0)) {
                    if (menu.selectedButtonIndex == 0) {
                        enterName = true;
                        isMenu = false;
                    }
                    if (menu.selectedButtonIndex == 1) {
                        PrintScore(ScoreTop);
                        ShowScore = true;
                        isMenu = false;
                    }
                    if (menu.selectedButtonIndex == 2) {
                        Credit = true;
                        isMenu = false;
                    }
                    if (menu.selectedButtonIndex == 3) {
                        window.close();
                    }
                }
            }
        }

        float movementDeltaTime = movementClock.restart().asSeconds();



        if (enterName) {

            sf::Text text;
            sf::Text title;
            sf::Text Enter;
            text.setFont(font);
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::White);
            text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100);
            text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
            title.setFont(font);
            title.setCharacterSize(50);
            title.setFillColor(sf::Color::White);
            title.setPosition(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 200);
            title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
            title.setString("Enter your name");
            Enter.setFont(font);
            Enter.setCharacterSize(50);
            Enter.setFillColor(sf::Color::White);
            Enter.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            Enter.setOrigin(Enter.getGlobalBounds().width / 2, Enter.getGlobalBounds().height / 2);
            Enter.setString("Press Enter to continue");

            while (enterName) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::TextEntered && name.size() < 12) {

                        if (event.text.unicode < 128 && event.text.unicode > 32) {
                            name += static_cast<char>(event.text.unicode);

                        }

                    }
                    if (event.type == sf::Event::KeyPressed) {

                        if (event.key.code == sf::Keyboard::Enter) {
                            isMenu = false;
                            enterName = false;
                            gameStarted = true;
                            continue;
                        }
                        if (event.key.code == sf::Keyboard::BackSpace && !name.empty()) {
                            name.pop_back();

                        }

                    }
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    }
                    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
                    text.setString(name);
                }
                window.clear();
                window.draw(backgroundScore);
                window.draw(text);
                window.draw(title);
                window.draw(Enter);
                window.display();
            }
        }

        if (ShowScore) {
            sf::Text title;
            sf::Text returnText;

            title.setFont(font);
            title.setCharacterSize(50);
            title.setFillColor(sf::Color::White);
            title.setPosition(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 200);
            title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
            title.setString("Scoreboard");

            returnText.setFont(font);
            returnText.setCharacterSize(50);
            returnText.setFillColor(sf::Color::White);
            returnText.setPosition(0 + 20, SCREEN_HEIGHT / 2 + 320);
            returnText.setOrigin(returnText.getGlobalBounds().width / 2, returnText.getGlobalBounds().height / 2);
            returnText.setString("Press Esc to return");

            for (int i = 0; i < 5; i++) {
                ScoreTop[i].setFont(font);
                ScoreTop[i].setCharacterSize(45);
                ScoreTop[i].setFillColor(sf::Color::White);
                ScoreTop[i].setPosition(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 100 + (i * 50));
            }
            while (ShowScore)
            {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Escape) {
                            ShowScore = false;
                            isMenu = true;
                            break;
                        }
                    }
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    }
                }
                window.clear();

                window.draw(backgroundScore); for (int i = 0; i < 5; i++) {
                    window.draw(ScoreTop[i]);
                }
                window.draw(title);
                window.draw(returnText);
                window.display();
            }
        }

        if (Credit) {
            sf::Text title;
            sf::Text returnText;
            while (Credit) {
                title.setFont(font);
                title.setCharacterSize(50);
                title.setFillColor(sf::Color::White);
                title.setPosition(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 200);
                title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
                title.setString("Credit");

                returnText.setFont(font);
                returnText.setCharacterSize(50);
                returnText.setFillColor(sf::Color::White);
                returnText.setPosition(0 + 20, SCREEN_HEIGHT / 2 + 320);
                returnText.setOrigin(returnText.getGlobalBounds().width / 2, returnText.getGlobalBounds().height / 2);
                returnText.setString("Press Esc to return");

                sf::Text text;

                text.setFont(font);
                text.setCharacterSize(45);
                text.setFillColor(sf::Color::White);
                text.setPosition(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 100);
                text.setString("Sorasak limthong 66010840");


                while (Credit)
                {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::KeyPressed) {
                            if (event.key.code == sf::Keyboard::Escape) {
                                Credit = false;
                                isMenu = true;
                                break;
                            }
                        }
                        if (event.type == sf::Event::Closed) {
                            window.close();
                            return 0;
                        }
                    }
                    window.clear();
                    window.draw(backgroundCredit);
                    window.draw(text);

                    window.draw(title);
                    window.draw(returnText);
                    window.display();
                }
            }
        }
        if (!gameStarted) {
            window.clear();
            menu.draw(window);
            window.display();
            continue;
        }

        if (isPause && !character->GetLevelUp()) {
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
            saveScore(name, character->getScore());
            goto restart;
        }
        if (character->GetLevelUp()) {

            int randAbility1 = rand() % 2;
            int randAbility2 = rand() % 2;
            while (randAbility1 == randAbility2) {
				randAbility2 = rand() % 2;
			}
            LevelUpGui levelUpGui(window, ability,randAbility1,randAbility2);
            std::cout << randAbility1 << " " << randAbility2 << std::endl;
            deltaTime = 0.0f;


            while (character->GetLevelUp())
            {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {

                        sf::Vector2f mousePosition(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

                        levelUpGui.isHoverButton1(mousePosition);
                        levelUpGui.isHoverButton2(mousePosition);

                        if (event.mouseButton.button == sf::Mouse::Left) {

                            //std::cout << "isClick" << std::endl;
                            if (levelUpGui.isPressButton1(mousePosition)) {
                                if (levelUpGui.abilityCanlevelup1 == 0) {
                                    bool isNewAbility = true;
                                    for (int i = 0; i < 3; i++) {
                                        if (ability[i].getType() == AbilityType::FireBall) {
                                            ability[i].LevelUp();
                                            character->isLevelUp = false;
                                            isNewAbility = false;
                                            break;
                                        }
                                    }
                                    if (isNewAbility) {
                                        for (int i = 0; i < 3; i++) {
                                            if (ability[i].getType() == AbilityType::None) {
                                                character->isLevelUp = false;
                                                break;
                                            }
                                        }
                                    }
                                }

                                if (levelUpGui.abilityCanlevelup1 == 1) {
                                    bool isNewAbility = true;
                                    for (int i = 0; i < 3; i++) {
                                        if (ability[i].getType() == AbilityType::CircleDamage) {
                                            ability[i].LevelUp();
                                            character->isLevelUp = false;
                                            isNewAbility = false;
                                            break;
                                        }
                                    }
                                    if (isNewAbility) {
                                        for (int i = 0; i < 3; i++) {
                                            if (ability[i].getType() == AbilityType::None) {
                                                Ability newAbility(4.5f, AbilityType::CircleDamage);
                                                ability[i] = newAbility;
                                                character->isLevelUp = false;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }

                            if (levelUpGui.isPressButton2(mousePosition)) {

                                if (levelUpGui.abilityCanlevelup2 == 0) {
                                    bool isNewAbility = true;
                                    for (int i = 0; i < 3; i++) {
                                        if (ability[i].getType() == AbilityType::FireBall) {
                                            ability[i].LevelUp();
                                            character->isLevelUp = false;
                                            isNewAbility = false;
                                            break;
                                        }
                                    }
                                    if (isNewAbility) {
                                        for (int i = 0; i < 3; i++) {
                                            if (ability[i].getType() == AbilityType::None) {
                                                Ability newAbility(4.5f, AbilityType::FireBall);
                                                ability[i] = newAbility;
                                                character->isLevelUp = false;
                                                break;
                                            }
                                        }
                                    }
                                }

                                if (levelUpGui.abilityCanlevelup2 == 1) {
                                    bool isNewAbility = true;
                                    for (int i = 0; i < 3; i++) {
                                        if (ability[i].getType() == AbilityType::CircleDamage) {
                                            ability[i].LevelUp();
                                            character->isLevelUp = false;
                                            isNewAbility = false;
                                            break;
                                        }
                                    }
                                    if (isNewAbility) {
                                        for (int i = 0; i < 3; i++) {
                                            if (ability[i].getType() == AbilityType::None) {
                                                Ability newAbility(4.5f, AbilityType::CircleDamage);
                                                ability[i] = newAbility;
                                                character->isLevelUp = false;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                        return 0;
                    }

                }
                window.clear();
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
                levelUpGui.setPosition(character->getSprite().getPosition());
                levelUpGui.Render(window);
                window.display();
            }

            character->initAbility();

        }
        if (enemies.size() <= 10 + (character->getTimer()/20)* 2 )  {

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

        for (int i = 0; i < 3; i++) {
            if (ability[i].canUse() && ability[i].getType() == AbilityType::FireBall) {
                for (int j = 0; j < ability[i].abilityInfo.amount; j++) {
                    //std::cout << ability[i].abilityInfo.level << std::endl;
                    if (enemies.size() > 0) {
                        int r = rand() % enemies.size();
                        sf::Vector2f posTarget(enemies[r].getSprite().getPosition().x, enemies[r].getSprite().getPosition().y);
                        sf::Vector2f posPlayer(character->getSprite().getPosition().x, character->getSprite().getPosition().y);
                        FireBall fireball(posPlayer, posTarget, ability[i].abilityInfo.baseDamage);
                        fireballs.push_back(fireball);
                    }
                }
                ability[i].use();
            }
            if (ability[i].canUse() && ability[i].getType() == AbilityType::CircleDamage) {
                for (int j = 0; j < ability[i].abilityInfo.amount; j++) {
                    if (enemies.size() > 0) {
                        int r = rand() % enemies.size();
                        sf::Vector2f posTarget(enemies[r].getSprite().getPosition().x, enemies[r].getSprite().getPosition().y);
                        circledamage circle(posTarget,ability[i].abilityInfo.radius, ability[i].abilityInfo.duration,ability[i].abilityInfo.Hitboxdelay);
                        damageCircles.push_back(circle);
                    }
                }
                ability[i].use();
            }
            ability[i].update(deltaTime);

        }

        character->move(movement, deltaTime);

        view.setCenter(static_cast<sf::Vector2f>(character->getSprite().getPosition()));
        window.setView(view);
        window.clear();
        myMap.draw(window);

        sf::FloatRect playerBounds = character->getSprite().getGlobalBounds();

        for (size_t i = 0; i < enemies.size(); ++i) {
            enemiesPositions.push_back(enemies[i].getSprite().getPosition());
            enemies[i].colWithOtherEnemy(enemies);
            enemies[i].moveToPlayer(character->getSprite().getPosition(), 195.0f * deltaTime);
            enemies[i].update(playerBounds);

            if (enemies[i].colWithPlayer(playerBounds)) {
				character->takeDamage(10);
			}

            if (enemies[i].isDead()) {
                character->updateScore(1);
                int rate = rand() % 100;

                if (rate <= 3) {
                    item.push_back(Item(enemies[i].getSprite().getPosition(), ItemType::HP));
                }
                else if (20 <= rate && rate <= 40) {
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

        for (auto it = damageCircles.begin(); it != damageCircles.end();) {
			it->update(deltaTime);
            it->takeDamageinCircle(enemies);
            if (it->isActive()) {
				it->draw(window);
                ++it;
			}
            else
            {
                it = damageCircles.erase(it);
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

