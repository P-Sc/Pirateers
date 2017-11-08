/**
 * @file physicssettings.h
 */

#ifndef PHYSICSSETTINGS_H
#define PHYSICSSETTINGS_H

#include <vector>
#include <memory>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include "base/settings.h"
#include "physics/entitycategory.h"

class b2World;

/**
 * @struct PhysicsSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit PhysicsComponent und PhysicsSystem benutzt.
 */
struct PhysicsSettings : Settings {
    float rotation = 0, density = 0,
          friction = 0.5f, restitution = 0, linearDamping = 0.5f, angularDamping = 3.0f;
    b2Vec2 pos;
    // TODO Deprecated
    float width = 0, height = 0;
    bool dynamic = true;
    EntityCategory category = ENTITY_DEFAULT;
    int collidingWith = 0xFFFF;
    std::vector<b2Shape*> shapes;

    b2World* world;
};


#endif // PHYSICSSETTINGS_H
