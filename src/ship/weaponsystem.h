/**
 * @file weaponsystem.h
 */
#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H

#include "base/gamesystem.h"
#include "ship/weaponcomponent.h"
#include "ship/weaponsettings.h"
#include "ship/weapon.h"
//#include <Box2D/Box2D.h>

class PhysicsSystem;
class GraphicsSystem;
class ModelDisplaySystem;
class AmmoSystem;
class b2World;

/**
 * @class WeaponSystem
 * @brief System zur Verwaltung von Waffen
 *
 * Lädt anhand des Namens WeaponSettings aus dem WeaponLoader,
 * verändert diese anhand der Weapon-Einstellungen, erstellt das WeaponComponent
 * und montiert diese an dem jeweiligen Schiff.
 * Ein WeaponComponent ist lediglich für die Waffe selbst zuständig - Ein AmmoComponent
 * dagegen für das Abfeuern der Projektile.
 */
class WeaponSystem : public GameSystem<WeaponComponent, WeaponSettings> {
private:
    PhysicsSystem& physicsSystem;
    GraphicsSystem& graphicsSystem;
    ModelDisplaySystem& modelDisplaySystem;
    AmmoSystem& ammoSystem;
    b2World* world;
public:
    virtual void update(float dt);
    virtual Handle* createComponent(Weapon weapon, Handle* shipPhysicsHandle);
    virtual void eraseComponent(unsigned int id);
    WeaponSystem(PhysicsSystem& physicsSystem, GraphicsSystem& graphicsSystem,
                 ModelDisplaySystem& modelDisplaySystem, AmmoSystem& ammoSystem);
};

#endif // WEAPONSYSTEM_H
