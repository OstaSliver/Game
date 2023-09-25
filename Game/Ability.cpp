#include "Ability.h"
#include <SFML/Graphics.hpp>

Ability::Ability(float cooldown) : cooldown(cooldown), elapsedTime(0.0f)
   {
    this->isReady = true;
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

    void  Ability::use() {
        if (isReady) {
            isReady = false;
        }
    }

