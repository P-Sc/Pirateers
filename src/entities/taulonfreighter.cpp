#include "taulonfreighter.h"
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

TaulonFreighter::TaulonFreighter(ShipSystem& shipSystem, AISystem& aiSystem,
                                 ShipSettings shipSettings, float multiplier)
    : EnemyShip(shipSystem, aiSystem) {

    EnergySettings energySettings;
    energySettings.maxEnergy = 5000;
    energySettings.regenPerSecond = 100;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 500;
    shieldSettings.maxShield = 10000;
    shieldSettings.regenPerSecond = 300;
    shieldSettings.maxRegenPause = 5;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "TaulonFreighter";
    float laserFireRate = 0.1f + (rand() % 4)/10.f;
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(1, 1)));
    shipSettings.weapons.back().rateOfFireMultiplier = laserFireRate;
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(-1, 1)));
    shipSettings.weapons.back().rateOfFireMultiplier = laserFireRate;
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(1, 0)));
    shipSettings.weapons.back().rateOfFireMultiplier = laserFireRate;
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(-1, 0)));
    shipSettings.weapons.back().rateOfFireMultiplier = laserFireRate;
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(1, -1)));
    shipSettings.weapons.back().rateOfFireMultiplier = laserFireRate;
    shipSettings.weapons.push_back(Weapon("laser", b2Vec2(-1, -1)));
    shipSettings.weapons.back().rateOfFireMultiplier = laserFireRate;
    shipSettings.weapons.push_back(Weapon("neutron", b2Vec2(0, 1)));
    shipSettings.weapons.push_back(Weapon("neutron", b2Vec2(0, -1)));
    //shipSettings.weapons.back().damageMultiplier = 0.01f;
    //shipSettings.weapons.back().velocityMultiplier = 0.7f;
    //shipSettings.weapons.back().rateOfFireMultiplier = 0.1f + (rand() % 4)/10.f;
    //shipSettings.weapons.back().velocityMultiplier = 0.7f;
    //shipSettings.weapons.back().rateOfFireMultiplier = 0.1f + (rand() % 4)/10.f;
    shipSettings.explosionDelay = 3;
    shipSettings.rewardCount = 20;
    shipSettings.engineEffectSettings.offset.Set(0, -7);
    shipSettings.engineEffectSettings.size = 7;
    this->shipSettings = shipSettings;
    aiSettings.type = AISettings::gunship;
    aiSettings.weaponRange = 160;
    aiSettings.combatRadius = 40;
    aiSettings.sightRange = 250;
    aiSettings.projectileVelocity = 150.f;

    create(multiplier);
}
