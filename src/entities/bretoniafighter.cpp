#include "bretoniafighter.h"
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

BretoniaFighter::BretoniaFighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                             float multiplier)
    : EnemyShip(shipSystem, aiSystem) {
    EnergySettings energySettings;
    energySettings.maxEnergy = 350;
    energySettings.regenPerSecond = 70;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 400;
    shieldSettings.maxShield = 200;
    shieldSettings.regenPerSecond = 100;
    shieldSettings.maxRegenPause = 2;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "BretoniaFighter";
    shipSettings.explosionDelay = 1;
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(0, 1)));
    shipSettings.weapons.back().damageMultiplier = 0.4f;
    shipSettings.weapons.back().rateOfFireMultiplier = 1.5f * (0.5f + (rand() % 10) / 10.f);
    shipSettings.weapons.back().scatterMultiplier = 0.5f;
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(1, 0)));
    shipSettings.weapons.back().damageMultiplier = 0.4f;
    shipSettings.weapons.back().rateOfFireMultiplier = 1.5f * (0.5f + (rand() % 10) / 10.f);
    shipSettings.weapons.back().scatterMultiplier = 0.5f;
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(-1, 0)));
    shipSettings.weapons.back().damageMultiplier = 0.4f;
    shipSettings.weapons.back().rateOfFireMultiplier = 1.5f * (0.5f + (rand() % 10) / 10.f);
    shipSettings.weapons.back().scatterMultiplier = 0.5f;
    //shipSettings.weapons.back().velocityMultiplier = 0.2f;
    shipSettings.rewardCount = 2;
    shipSettings.engineEffectSettings.offset.Set(0, -3);
    shipSettings.engineEffectSettings.size = 4;
    this->shipSettings = shipSettings;
    aiSettings.type = AISettings::fighter;
    aiSettings.weaponRange = 160;
    aiSettings.combatRadius = 10 + rand() % 20;
    aiSettings.sightRange = 300;

    create(multiplier);
}
