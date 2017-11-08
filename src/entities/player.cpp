#include "player.h"

#include "input/shipinputsystem.h"
#include "ship/shipsystem.h"
#include "physics/physicssystem.h"
#include "camera/camerasystem.h"
#include "gamelogic/aisystem.h"
#include "gamelogic/rewardsystem.h"
#include "gamelogic/shopsystem.h"
#include "gui/statusinformationsystem.h"
#include "gamelogic/teleportsystem.h"


Handle*Player::getShipHandle() {
    return shipHandle;
}

Handle*Player::getTeleportHandle() {
    return teleportHandle;
}

void Player::destroy() {
    if (shipHandle != nullptr) {
        delete shipHandle;
    }

    if (teleportHandle != nullptr) {
        delete teleportHandle;
    }
}

void Player::create() {
    EnergySettings energySettings;
    energySettings.maxEnergy = 500;
    energySettings.regenPerSecond = 100;

    ShieldSettings shieldSettings;
    shieldSettings.maxHull = 500;
    shieldSettings.maxShield = 500;
    shieldSettings.regenPerSecond = 50;
    shieldSettings.maxRegenPause = 3;

    ShipSettings shipSettings;
    shipSettings.energySettings = energySettings;
    shipSettings.shieldSettings = shieldSettings;
    shipSettings.shipname = "Raider I";
    shipSettings.pos = position;
    shipSettings.weapons.push_back(Weapon(slot1, b2Vec2(0, 0)));
    shipSettings.weapons.back().enableShake = true;
    shipSettings.weapons.push_back(Weapon(slot2, b2Vec2(1, -1)));
    shipSettings.weapons.back().enableShake = true;
    shipSettings.weapons.push_back(Weapon(slot3, b2Vec2(-1, -1)));
    shipSettings.weapons.back().enableShake = true;
    shipSettings.engineEffectSettings.offset.Set(0, -2);
    shipHandle = shipSystem.createComponent(shipSettings);
    shipInputSystem.registerShipAsListener(shipHandle);
    Handle* playerPhysicsHandle = shipSystem.getPhysicsHandle(shipHandle->id);
    physicsSystem.registerSystemAsListener(playerPhysicsHandle->id, evMove,
                                           cameraSystem.getEventManager());
    shipSystem.registerSystemAsListener(shipHandle->id, evMove, aiSystem.getEventManager());
    shipSystem.registerSystemAsListener(shipHandle->id, evMove, rewardSystem.getEventManager());
    shipSystem.registerSystemAsListener(shipHandle->id, evMove, shopSystem.getEventManager());
    shipSystem.registerSystemAsListener(shipHandle->id, evDestroyed, shopSystem.getEventManager());
    shipSystem.registerSystemAsListener(shipHandle->id, evMove, statusInformationSystem.getEventManager());
    shipSystem.registerSystemAsListener(shipHandle->id, evShield, statusInformationSystem.getEventManager());
    shipSystem.registerSystemAsListener(shipHandle->id, evEnergyStatus, statusInformationSystem.getEventManager());
    shopSystem.setPlayerHandle(shipHandle);

    teleportHandle = teleportSystem.createComponent(Settings());
    shipSystem.registerComponentAsListener(shipHandle->id, evMove, teleportHandle->id,
                                           teleportSystem.getEventManager());
    shipInputSystem.registerComponentAsListener(0, cmStartTeleport, teleportHandle->id,
            teleportSystem.getEventManager());
    teleportSystem.registerComponentAsListener(teleportHandle->id, cmActivate, shipHandle->id,
            shipSystem.getEventManager());
    teleportSystem.registerComponentAsListener(teleportHandle->id, cmDeactivate, shipHandle->id,
            shipSystem.getEventManager());

    statusInformationSystem.setShipSettings(shipSettings);
}

void Player::setWeapons(std::string slot1, std::string slot2, std::string slot3) {
    this->slot1 = slot1;
    this->slot2 = slot2;
    this->slot3 = slot3;
}

void Player::setPosition(b2Vec2 pos) {
    this->position = pos;
}

Player::Player(ShipSystem& shipSystem, ShipInputSystem& shipInputSystem,
               PhysicsSystem& physicsSystem, CameraSystem& cameraSystem, AISystem& aiSystem,
               RewardSystem& rewardSystem, ShopSystem& shopSystem,
               StatusInformationSystem& statusInformationSystem, TeleportSystem& teleportSystem)
    : shipSystem(shipSystem), shipInputSystem(shipInputSystem), physicsSystem(physicsSystem)
    , cameraSystem(cameraSystem), aiSystem(aiSystem), rewardSystem(rewardSystem)
    , shopSystem(shopSystem), statusInformationSystem(statusInformationSystem)
    , teleportSystem(teleportSystem) {

}

Player::~Player() {
    destroy();
}
