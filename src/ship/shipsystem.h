/**
 * @file shipsystem.h
 */
#ifndef SHIPSYSTEM_H
#define SHIPSYSTEM_H

#include "base/gamesystem.h"
#include "ship/shipcomponent.h"
#include "ship/shipsettings.h"
#include "utils/shipparser.h"

class PhysicsSystem;
class GraphicsSystem;
class ModelDisplaySystem;
class WeaponSystem;
class TagSystem;
class ShieldSystem;
class EnergySystem;
class ExplosionSystem;
class RewardSystem;
class EngineEffectSystem;


/**
 * @class ShipSystem
 * @brief System zur Verwaltung von Schiffen.
 *
 * Erstellt jedes ShipComponent. Erzeugt bei jeder Zerstörung Explosionen und Credits.
 */
class ShipSystem : public GameSystem<ShipComponent, ShipSettings> {
private:
    PhysicsSystem& physicsSystem;
    GraphicsSystem& graphicsSystem;
    ModelDisplaySystem& modelDisplaySystem;
    WeaponSystem& weaponSystem;
    TagSystem& tagSystem;
    ShieldSystem& shieldSystem;
    EnergySystem& energySystem;
    ExplosionSystem& explosionSystem;
    RewardSystem& rewardSystem;
    EngineEffectSystem& engineEffectSystem;
    ShipParser parser;

    void spawnRewards(b2Vec2 pos, int count, int areaSize);
    void registerListeners(Handle *handle);
public:
    Handle * getGraphicsHandle(unsigned int shipId);
    Handle * getPhysicsHandle(unsigned int shipId);
    Handle * getModelHandle(unsigned int shipId);
    Handle * getWeaponHandle(unsigned int shipId);
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(ShipSettings& settings);
    virtual void eraseComponent(unsigned int id);
    ShipSystem(PhysicsSystem& physicsSystem, GraphicsSystem& graphicsSystem,
               ModelDisplaySystem& modelDisplaySystem, WeaponSystem& weaponSystem,
               TagSystem& tagSystem, ShieldSystem& shieldSystem, EnergySystem& energySystem,
               ExplosionSystem& explosionSystem, RewardSystem& rewardSystem,
               EngineEffectSystem& engineEffectSystem);
};

#endif // SHIPSYSTEM_H
