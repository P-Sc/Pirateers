#include "banditdrone.h"

BanditDrone::BanditDrone(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                         float multiplier)
    : EnemyShip(shipSystem, aiSystem) {

    EnergySettings energySettings;
    energySettings.maxEnergy = 500;
    energySettings.regenPerSecond = 50;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 200;
    shieldSettings.maxShield = 300;
    shieldSettings.regenPerSecond = 50;
    shieldSettings.maxRegenPause = 3;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "BanditDrone";
    shipSettings.explosionDelay = 0;
    shipSettings.weapons.push_back(Weapon("taychon", b2Vec2(0, 0)));
    shipSettings.weapons.back().damageMultiplier = 1.6f;
    shipSettings.weapons.back().rateOfFireMultiplier = (0.3f + (rand() % 5)/10.f);
    shipSettings.rewardCount = 1;
    shipSettings.engineEffectSettings.active = false;
    this->shipSettings = shipSettings;
    aiSettings.type = AISettings::drone;
    aiSettings.weaponRange = 160;
    aiSettings.combatRadius = 10 + rand() % 30;
    aiSettings.sightRange = 200;
    aiSettings.projectileVelocity = 220.f;

    create(multiplier);
}
