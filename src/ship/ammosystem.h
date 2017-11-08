/**
 * @ammosystem.h
 */
#ifndef AMMOSYSTEM_H
#define AMMOSYSTEM_H

#include "base/gamesystem.h"
#include "ship/ammocomponent.h"
#include "ship/ammosettings.h"

class PhysicsSystem;
class GraphicsSystem;
class LightSystem;
class CameraShakeSystem;
class SoundSystem;

/**
 * @class AmmoSystem
 * @brief System zur Verwaltung von AmmoComponent und Projektilen (Projectile)
 *
 * Erstellt ein AmmoComponent und erstellt ggf. Projectile-Arrays neu, falls nötig
 * (z.B. bei Änderungen der Feuerrate). Diese Arrays sind Pools von wiederverwendbaren
 * Projektilen, damit nicht bei jedem Schuss ein neues Projektil erstellt werden muss.
 */
class AmmoSystem : public GameSystem<AmmoComponent, AmmoSettings> {
private:
    PhysicsSystem& physicsSystem;
    GraphicsSystem& graphicsSystem;
    LightSystem& lightSystem;
    CameraShakeSystem& cameraShakeSystem;
    SoundSystem& soundSystem;

    void createComponentProjectiles(unsigned int index);
public:
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(AmmoSettings settings);
    virtual void eraseComponent(unsigned int id);
    AmmoSystem(PhysicsSystem& physicsSystem, GraphicsSystem& graphicsSystem,
               LightSystem& lightSystem, CameraShakeSystem& cameraShakeSystem,
               SoundSystem& soundSystem);
};

#endif // AMMOSYSTEM_H
