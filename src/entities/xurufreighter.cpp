#include "xurufreighter.h"
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

XuruFreighter::XuruFreighter(ShipSystem& shipSystem, AISystem& aiSystem,
                             ShipSettings shipSettings, float multiplier)
    : EnemyShip(shipSystem, aiSystem) {


    EnergySettings energySettings;
    energySettings.maxEnergy = 100;
    energySettings.regenPerSecond = 50;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 3000;
    shieldSettings.maxShield = 300;
    shieldSettings.regenPerSecond = 100;
    shieldSettings.maxRegenPause = 5;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "XuruFreighter";
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(0, 1)));
    //shipSettings.weapons.back().damageMultiplier = 0.01f;
    //shipSettings.weapons.back().velocityMultiplier = 0.7f;
    shipSettings.weapons.back().rateOfFireMultiplier = 0.3f + (rand() % 4)/10.f;
    shipSettings.weapons.back().damageMultiplier = 0.3;
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(0, -1)));
    //shipSettings.weapons.back().velocityMultiplier = 0.7f;
    shipSettings.weapons.back().rateOfFireMultiplier = 0.3f + (rand() % 4)/10.f;
    shipSettings.weapons.back().damageMultiplier = 0.3;
    shipSettings.explosionDelay = 3;
    shipSettings.rewardCount = 14;
    shipSettings.engineEffectSettings.offset.Set(0, -5);
    shipSettings.engineEffectSettings.size = 6;
    this->shipSettings = shipSettings;
    aiSettings.type = AISettings::freighter;
    aiSettings.weaponRange = 160;
    aiSettings.combatRadius = 15;
    aiSettings.sightRange = 250;
    aiSettings.projectileVelocity = 150.f;

    create(multiplier);
}
