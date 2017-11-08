/**
 * @file physicssystem.h
 */

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "base/gamesystem.h"
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2World.h>
#include "physics/physicssettings.h"
#include "physics/physicscomponent.h"

/**
 * @class PhysicsSystem
 * @brief GameSystem für alle physikalischen Objekte
 *
 * Wird mit PhysicsComponent und PhysicsSettings benutzt.
 * Arbeitet mit Box2D.
 */
class PhysicsSystem : public GameSystem<PhysicsComponent, PhysicsSettings> {
private:
    float timeStep = 1.0f/60.0f;
    int32 velocityIterations = 4;
    int32 positionIterations = 2;
    b2Vec2 gravity;
    b2World* world;
public:
    b2World* getWorld();
    b2Body* getBody(unsigned int id);
    virtual void update(float dt);
    virtual Handle* createComponent(PhysicsSettings settings);
    virtual void eraseComponent(unsigned int id);
    PhysicsSystem();
    //~PhysicsSystem();
};

#endif // PHYSICSSYSTEM_H
