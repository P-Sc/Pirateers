#include "xurugunship.h"

#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

XuruGunship::XuruGunship(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                         float multiplier)
    : EnemyShip(shipSystem, aiSystem) {

    EnergySettings energySettings;
    energySettings.maxEnergy = 1000;
    energySettings.regenPerSecond = 200;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 7000;
    shieldSettings.maxShield = 500;
    shieldSettings.regenPerSecond = 100;
    shieldSettings.maxRegenPause = 5;

    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "XuruGunship";
    std::uniform_int_distribution<> dist(0,30);
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(-1, 1)));
    shipSettings.weapons.back().rateOfFireMultiplier = 0.6f + dist(eng)/100.f;
    shipSettings.weapons.back().damageMultiplier = 0.3;
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(-1, -1)));
    shipSettings.weapons.back().rateOfFireMultiplier = 0.6f + dist(eng)/100.f;
    shipSettings.weapons.back().damageMultiplier = 0.3;
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(1, 1)));
    shipSettings.weapons.back().rateOfFireMultiplier = 0.6f + dist(eng)/100.f;
    shipSettings.weapons.back().damageMultiplier = 0.3;
    shipSettings.weapons.push_back(Weapon("plasma", b2Vec2(1, -1)));
    shipSettings.weapons.back().rateOfFireMultiplier = 0.6f + dist(eng)/100.f;
    shipSettings.weapons.back().damageMultiplier = 0.3;
    shipSettings.rewardCount = 7;
    shipSettings.engineEffectSettings.offset.Set(0, -6);
    shipSettings.engineEffectSettings.size = 6;
    this->shipSettings = shipSettings;

    shipSettings.explosionDelay = 4;
    aiSettings.type = AISettings::gunship;
    aiSettings.weaponRange = 150;
    dist = std::uniform_int_distribution<>(0,60);
    aiSettings.combatRadius = 30 + dist(eng);
    aiSettings.sightRange = 400;

    create(multiplier);
}
