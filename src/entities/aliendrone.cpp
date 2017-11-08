#include "aliendrone.h"
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

AlienDrone::AlienDrone(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                       float multiplier)
    : EnemyShip(shipSystem, aiSystem) {

    EnergySettings energySettings;
    energySettings.maxEnergy = 500;
    energySettings.regenPerSecond = 50;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 100;
    shieldSettings.maxShield = 200;
    shieldSettings.regenPerSecond = 50;
    shieldSettings.maxRegenPause = 3;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "AlienDrone";
    shipSettings.explosionDelay = 0;
    shipSettings.weapons.push_back(Weapon("taychon", b2Vec2(0, 0)));
    shipSettings.weapons.back().damageMultiplier = 0.2f;
    shipSettings.weapons.back().rateOfFireMultiplier = 1.f * (0.5f + (rand() % 10)/10.f);
    shipSettings.rewardCount = 1;
    shipSettings.engineEffectSettings.active = false;
    this->shipSettings = shipSettings;
    aiSettings.type = AISettings::drone;
    aiSettings.weaponRange = 160;
    aiSettings.combatRadius = 10 + rand() % 30;
    aiSettings.sightRange = 200;

    create(multiplier);
}
