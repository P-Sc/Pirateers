#include "banditfreighter.h"
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

BanditFreighter::BanditFreighter(ShipSystem& shipSystem, AISystem& aiSystem,
                                 ShipSettings shipSettings, float multiplier)
    : EnemyShip(shipSystem, aiSystem) {

    EnergySettings energySettings;
    energySettings.maxEnergy = 1000;
    energySettings.regenPerSecond = 50;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 1000;
    shieldSettings.maxShield = 1000;
    shieldSettings.regenPerSecond = 100;
    shieldSettings.maxRegenPause = 5;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "BanditFreighter";
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(0, 1)));
    //shipSettings.weapons.back().damageMultiplier = 0.01f;
    //shipSettings.weapons.back().velocityMultiplier = 0.7f;
    shipSettings.weapons.back().rateOfFireMultiplier = 0.8f + (rand() % 4)/10.f;
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(0, -1)));
    //shipSettings.weapons.back().velocityMultiplier = 0.7f;
    shipSettings.weapons.back().rateOfFireMultiplier = 0.8f + (rand() % 4)/10.f;
    shipSettings.explosionDelay = 3;
    shipSettings.rewardCount = 10;
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
