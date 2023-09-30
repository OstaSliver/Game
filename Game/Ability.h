

#ifndef ABILITY_H
#define ABILITY_H

class Ability {
public:
    Ability(float cooldown);

    void update(float deltaTime);

    bool canUse() const;

    void use();


private:
    int level;
    int amount;
    int baseDamage;
    int Area;
    int speed;

    float cooldown;
    float elapsedTime;
    bool isReady;
};

#endif 