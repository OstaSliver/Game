#pragma once
#include <SFML/Graphics.hpp>

enum class AbilityType {
    None,
    FireBall,
    CircleDamage,
};

struct AbilityInfo {
	int level;
	int amount;
	int baseDamage;
	int Area;
	int speed;
    float radius;
    float duration;
    float Hitboxdelay;
};

class Ability {

public:
    Ability(float cooldown,AbilityType abilityType);

    AbilityInfo abilityInfo;

    void update(float deltaTime);
    void LevelUp();
    bool canUse() const;
    AbilityType getType() const;
    void use();

private:
    
    AbilityType type;
    float cooldown;
    float elapsedTime;
    bool isReady;
};

