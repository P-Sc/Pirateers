/**
 * @file physicscomponent.h
 */

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "base/component.h"
#include <box2d/box2d.h>

class PhysicsSettings;

/**
 * @class PhysicsComponent
 * @brief Eine Physikkomponente
 *
 * Wird mit PhysicsSystem und PhysicsSettings benutzt.
 */
class PhysicsComponent : public Component {
private:
    b2BodyDef bodyDef;
    b2PolygonShape dynamicBox;
    b2CircleShape dynamicCircle;
    b2FixtureDef fixtureDef;
    b2World* world;
public:
    b2Body* body;
    bool rotating = false;
    float torque = 0, thrust = 0;
    b2Vec2 rotationVector;
    b2Vec2 localCenter;
    virtual void notify(EventMessage * message);

    PhysicsComponent(PhysicsSettings settings, Handle* handle);
    //PhysicsComponent(PhysicsComponent&& other) noexcept;
    virtual ~PhysicsComponent();
};

#endif // PHYSICSCOMPONENT_H
