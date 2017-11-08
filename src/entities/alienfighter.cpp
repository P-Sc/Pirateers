#include "alienfighter.h"
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

AlienFighter::AlienFighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                           float multiplier)
    : EnemyShip(shipSystem, aiSystem) {

    EnergySettings energySettings;
    energySettings.maxEnergy = 350;
    energySettings.regenPerSecond = 30;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 350;
    shieldSettings.maxShield = 350;
    shieldSettings.regenPerSecond = 70;
    shieldSettings.maxRegenPause = 2;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "AlienFighter";
    shipSettings.explosionDelay = 1;
    shipSettings.weapons.push_back(Weapon("taychon", b2Vec2(-1, 0)));
    shipSettings.weapons.back().damageMultiplier = 0.4f;
    shipSettings.weapons.back().rateOfFireMultiplier = 0.7f * (0.5f + (rand() % 10) / 10.f);
    shipSettings.weapons.back().scatterMultiplier = 0.5f;
    shipSettings.weapons.push_back(Weapon("taychon", b2Vec2(1, 0)));
    shipSettings.weapons.back().damageMultiplier = 0.4f;
    shipSettings.weapons.back().rateOfFireMultiplier = 0.7f * (0.5f + (rand() % 10) / 10.f);
    shipSettings.weapons.back().scatterMultiplier = 0.5f;
    shipSettings.rewardCount = 2;
    shipSettings.engineEffectSettings.active = false;
    this->shipSettings = shipSettings;
    aiSettings.type = AISettings::fighter;
    aiSettings.weaponRange = 130;
    aiSettings.combatRadius = 10 + rand() % 20;
    aiSettings.sightRange = 300;

    create(multiplier);
}
