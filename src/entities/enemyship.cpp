#include "enemyship.h"

void EnemyShip::multiply(float factor) {
    shipSettings.shieldSettings.maxHull *= factor;
    shipSettings.shieldSettings.maxShield *= factor;
    shipSettings.shieldSettings.regenPerSecond *= factor;

    shipSettings.energySettings.maxEnergy *= factor;
    shipSettings.energySettings.regenPerSecond *= factor;
    shipSettings.rewardCount = shipSettings.rewardCount * factor;

    for (size_t i = 0; i < shipSettings.weapons.size(); i++) {
        shipSettings.weapons[i].damageMultiplier *= factor;
    }
}

void EnemyShip::create(float factor) {
    multiply(factor);
    shipHandle = shipSystem.createComponent(shipSettings);
    aiHandle = aiSystem.createComponent(aiSettings);
    aiSystem.registerComponentAsListener(aiHandle->id, cmPowerEngines,
                                         shipHandle->id, shipSystem.getEventManager());
    aiSystem.registerComponentAsListener(aiHandle->id, cmRotateTo,
                                         shipHandle->id, shipSystem.getEventManager());
    aiSystem.registerComponentAsListener(aiHandle->id, cmStopRotating,
                                         shipHandle->id, shipSystem.getEventManager());
    aiSystem.registerComponentAsListener(aiHandle->id, cmAimAt,
                                         shipHandle->id, shipSystem.getEventManager());
    aiSystem.registerComponentAsListener(aiHandle->id, cmOpenFire,
                                         shipHandle->id, shipSystem.getEventManager());
    aiSystem.registerComponentAsListener(aiHandle->id, cmCeaseFire,
                                         shipHandle->id, shipSystem.getEventManager());

    shipSystem.registerComponentAsListener(shipHandle->id, evMove,
                                           aiHandle->id, aiSystem.getEventManager());
    shipSystem.registerComponentAsListener(shipHandle->id, evShield,
                                           aiHandle->id, aiSystem.getEventManager());
    shipSystem.registerComponentAsListener(shipHandle->id, evEnergyStatus,
                                           aiHandle->id, aiSystem.getEventManager());
    shipSystem.registerComponentAsListener(shipHandle->id, evDestroyed,
                                           aiHandle->id, aiSystem.getEventManager());
}

EnemyShip::EnemyShip(ShipSystem& shipSystem, AISystem& aiSystem)
    : shipSystem(shipSystem), aiSystem(aiSystem) {
}

EnemyShip::~EnemyShip() {
    delete shipHandle;
    delete aiHandle;
}
