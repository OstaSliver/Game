#ifndef ABILITY_H
#define ABILITY_H

enum class AbilityType {
    None,
    FireBall,
    IceBall,
    LightningBall,
    FireWall,
};

struct AbilityInfo {
	int level;
	int amount;
	int baseDamage;
	int Area;
	int speed;
};

class Ability {

public:
    Ability(float cooldown,AbilityType abilityType);

    void update(float deltaTime);

    bool canUse() const;
    AbilityType getType() const;
    void use();


private:
    
    AbilityType type;
    
    float cooldown;
    float elapsedTime;
    bool isReady;
};

#endif 