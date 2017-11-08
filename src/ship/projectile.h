/**
 * @file projectile.h
 */

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "handle.h"
#include "physics/entitycategory.h"

/**
 * @class Projectile
 * @brief Ein Projektil. Bewegt sich nach Einstellungen fort und speichert eine Kollision
 */
class Projectile : public b2RayCastCallback {
public:
    Handle* graphicsHandle = nullptr;
    Handle* lightHandle = nullptr;
    Handle* notColliding;
    b2Vec2 pos;
    b2Vec2 vel;
    b2Vec2 nextPos;
    //bool isActive = false;
    float rotation = 0;
    float lifetime = 0;
    bool hit = false, visible = false;
    Handle* targetHandle = nullptr;

    /**
     * @brief Ein Stück weiterfliegen
     * @param dt Vergangene Zeit in ms
     *
     * Strecke wird anhand der vergangenen Zeit und der eingestellten Geschwindigkeit ermittelt
     */
    void step(float dt) {
        pos = nextPos;
        nextPos += b2Vec2(vel.x *  dt / 1000.f, vel.y *  dt / 1000.f);
        EventPosMessage* moveMessage = new EventPosMessage;
        moveMessage->event = evMove;
        moveMessage->receiverId = graphicsHandle->id;
        moveMessage->pos = pos;
        moveMessage->rotation = rotation;
        graphicsHandle->system->notifyComponent(moveMessage);

        moveMessage = new EventPosMessage;
        moveMessage->event = evMove;
        moveMessage->receiverId = lightHandle->id;
        moveMessage->pos = pos;
        moveMessage->rotation = rotation;
        lightHandle->system->notifyComponent(moveMessage);
    }

    /**
     * @brief Funktion aus b2RayCastCallback. Wird bei einem Raycast aufgerufen, falls eine
     *        Kollision auftrat. Siehe Box2D-Dokumentation.
     */
    virtual float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point,
                                  const b2Vec2 &normal, float32 fraction) {
        Handle* physicsHandle = (Handle*) fixture->GetUserData();

        if (physicsHandle != notColliding
                && fixture->GetFilterData().categoryBits != ENTITY_WEAPON) {
            hit = true;
            targetHandle = physicsHandle;
            pos = point;
            return fraction;
        } else {
            return -1;
        }
    }

    virtual ~Projectile() {
        delete graphicsHandle;
        delete lightHandle;
    }
};


#endif // PROJECTILE_H
