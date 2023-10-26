#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position);

    void update(const sf::FloatRect& playerBounds);
    void takeDamage(int damage);

    bool isDead() ;
    bool colWithPlayer(const sf::FloatRect& playerBounds);

    void draw(sf::RenderWindow& window);
    void drawHp(sf::RenderWindow& window);
    void colWithOtherEnemy(std::vector<Enemy>& enemies);
    void moveToPlayer(const sf::Vector2f& pos_Player, float speed);
    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::FloatRect EnemyBounds = sprite.getGlobalBounds();
    int maxHP;
    int currentHP;
    bool dead;
 
};