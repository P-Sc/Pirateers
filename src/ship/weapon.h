/**
 * @file weapon.h
 */
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "handle.h"

/**
 * @struct Weapon
 * @brief Einstellungsklasse für Waffen. Enthält nur Namen für voreingestellten Waffentyp,
 *        Informationen für Waffe selbst und Multiplikatoren.
 */
struct Weapon {
    std::string gunName;
    b2Vec2 entityAnchor;
    float lowerAngle = 0, upperAngle = 0;
    bool enableLimit = false;
    bool enableShake = false;
    float damageMultiplier = 1,
          rateOfFireMultiplier = 1,
          velocityMultiplier = 1,
          scatterMultiplier = 1;
    int slot = -1;

    Weapon(std::string gunName, b2Vec2 entityAnchor)
        : gunName(gunName), entityAnchor(entityAnchor) {}

    Weapon(std::string gunName, b2Vec2 entityAnchor, float lowerAngle, float upperAngle)
        : Weapon(gunName, entityAnchor) {

        this->lowerAngle = lowerAngle;
        this->upperAngle = upperAngle;
    }
};


#endif // WEAPON_H
