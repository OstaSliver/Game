#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position, float radius, const sf::Color& color);

    void update(const sf::FloatRect& playerBounds);
    void takeDamage(int damage);
    bool isDead() ;
    void draw(sf::RenderWindow& window);
    bool colWithPlayer(const sf::FloatRect& playerBounds);
    void moveToPlayer(const sf::Vector2f& pos_Player, float speed);


private:

    sf::CircleShape circle;
    int maxHP;
    int currentHP;
    bool dead;
 

};
