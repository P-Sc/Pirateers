#ifndef PLAYER_H
#define PLAYER_H

//#include "input/inputsystem.h"
#include "handle.h"

class ShipSystem;
class ShipInputSystem;
class PhysicsSystem;
class CameraSystem;
class AISystem;
class RewardSystem;
class ShopSystem;
class StatusInformationSystem;
class TeleportSystem;

class Player {
private:
    ShipSystem& shipSystem;
    ShipInputSystem& shipInputSystem;
    PhysicsSystem& physicsSystem;
    CameraSystem &cameraSystem;
    AISystem& aiSystem;
    RewardSystem& rewardSystem;
    ShopSystem& shopSystem;
    StatusInformationSystem& statusInformationSystem;
    TeleportSystem& teleportSystem;

    Handle* shipHandle = nullptr;
    Handle* teleportHandle = nullptr;

    std::string slot1 = "laser", slot2 = "laser", slot3 = "laser";
    b2Vec2 position;
public:
    Handle* getShipHandle();
    Handle* getTeleportHandle();
    void destroy();
    void create();
    void setWeapons(std::string slot1, std::string slot2, std::string slot3);
    void setPosition(b2Vec2 pos);
    Player(ShipSystem& shipSystem, ShipInputSystem& shipInputSystem, PhysicsSystem& physicsSystem,
           CameraSystem &cameraSystem, AISystem& aiSystem, RewardSystem& rewardSystem,
           ShopSystem& shopSystem, StatusInformationSystem& statusInformationSystem,
           TeleportSystem& teleportSystem);
    ~Player();
};

#endif // PLAYER_H
