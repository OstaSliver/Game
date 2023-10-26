#include "Ability.h"
#include <SFML/Graphics.hpp>
#include "FireBall.h"
#include "Enemy.h"

Ability::Ability(float cooldown, AbilityType abilityType) : cooldown(cooldown), elapsedTime(0.0f), isReady(true), type(abilityType)
{
    if (type == AbilityType::FireBall) {
        abilityInfo.level = 1;
        abilityInfo.amount = 1;
        abilityInfo.baseDamage = 100;
        abilityInfo.Area = 0;
        abilityInfo.speed = 10;
    }

    if (type == AbilityType::CircleDamage) {
		abilityInfo.level = 1;
		abilityInfo.amount = 1;
		abilityInfo.baseDamage = 100;
		abilityInfo.Area = 100;
		abilityInfo.speed = 0;
		abilityInfo.radius = 100;
		abilityInfo.duration = 2.0f;
		abilityInfo.Hitboxdelay = 0.25f;
	}
}

void Ability::update(float deltaTime) {
    if (!isReady) {
        elapsedTime += deltaTime;
        if (elapsedTime >= cooldown) {
            isReady = true;
            elapsedTime = 0.0f;
        }
    }
}

void Ability::LevelUp()
{
    switch (type) {
    case AbilityType::FireBall:
        switch (abilityInfo.level) {
        case 1:
            abilityInfo.level = 2;
            abilityInfo.baseDamage = 200;
            break;
        case 2:
            abilityInfo.level = 3;
            abilityInfo.amount = 2;
            break;
        case 3:
            abilityInfo.level = 4;
            abilityInfo.baseDamage = 300;
            break;
        case 4:
            abilityInfo.level = 5;
            abilityInfo.amount = 3;
            break;
        case 5:
            abilityInfo.level = 6;
            abilityInfo.baseDamage = 400;
            break;
        case 6:
            abilityInfo.level = 7;
            abilityInfo.amount = 4;
            break;
        }
        break;
    case AbilityType::CircleDamage:
        switch (abilityInfo.level) {
        case 1:
            abilityInfo.level = 2;
            abilityInfo.amount = 2;
            abilityInfo.radius = 120;
            break;
        case 2:
            abilityInfo.level = 3;
            abilityInfo.duration = 2.5f;
            abilityInfo.baseDamage = 110;
            break;
        case 3:
            abilityInfo.level = 4;
            abilityInfo.amount = 3;
            abilityInfo.radius = 140;
            break;
        case 4:
            abilityInfo.level = 5;
            abilityInfo.duration = 3.0f;
            abilityInfo.baseDamage = 120;
            break;
        case 5:
            abilityInfo.level = 6;
            abilityInfo.amount = 4;
            abilityInfo.radius = 160;
            break;
        case 6:
            abilityInfo.level = 7;
            abilityInfo.duration = 3.5f;
            abilityInfo.baseDamage = 125;
            break;
        case 7:
            abilityInfo.level = 8;
            abilityInfo.radius = 180;
            abilityInfo.baseDamage = 130;
            break;
        }
        break;
    }
}


bool Ability::canUse() const {
    return isReady;
}

AbilityType Ability::getType() const
{
    return type;
}


void  Ability::use() {
    if (isReady) {
        isReady = false;
    }
}

