#include "Ability.h"
#include <SFML/Graphics.hpp>
#include "FireBall.h"

Ability::Ability(float cooldown, AbilityType abilityType): cooldown(cooldown), elapsedTime(0.0f), isReady(true), type(abilityType)
{
    

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

