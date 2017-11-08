/**
 * @file ammocomponent.h
 */

#ifndef AMMOCOMPONENT_H
#define AMMOCOMPONENT_H

#include <vector>
#include <random>
#include "Box2D/Common/b2Math.h"
#include "base/component.h"
#include "ship/ammosettings.h"
#include "ship/projectile.h"

//class GraphicsSystem;
//class LightSystem;
class PhysicsSystem;

/**
 * @class AmmoComponent
 * @brief Komponente für Projektile von Waffen.
 *
 * Wird mit AmmoSettings und AmmoSystem benutzt.
 */
class AmmoComponent : public Component
{
private:
    PhysicsSystem* physicsSystem;
    b2Vec2 spawningPos, spawningVel;
    std::random_device* r;
    std::mt19937* gen;
    bool firing = false;

    std::uniform_real_distribution<>* dist;

    void reportHit(Projectile* p);
    void reportFire();
public:
    AmmoSettings settings;
    Handle* soundHandle = nullptr;
    Handle* cameraShakeHandle = nullptr;
    std::vector<Projectile*> idleProjectiles;
    std::vector<Projectile*> activeProjectiles;
    float maxProjectileLifetime = 0, firingGap = 1.f, idleDuration = 0.f, spawningDir = 0.f,
          currentEnergy = 0, maxEnergy = 1;
    bool requiresNewSize = false;

    bool isFiring();
    void setVisible(Projectile* p, bool isActive);
    //void setGraphicsSystem(GraphicsSystem* value);
    void setPhysicsSystem(PhysicsSystem* value);
    void tick(float dt);
    void fire(float dt);
    virtual void notify(EventMessage *message);
    AmmoComponent(AmmoSettings settings, Handle* handle);
};

#endif // AMMOCOMPONENT_H
