#include "physicscomponent.h"
#include "physics/physicssettings.h"
#include "box2d/b2_polygon_shape.h"

using std::vector;

/**
 * @copydoc Component::notify
 * - ::ApplyForce Anschieben, Kraft ansetzen
 * - ::cmRotateTo Zu einem Punkt drehen
 * - ::cmStopRotating Aufhören zu drehen
 * - ::evMove Position, Rotation und Geschwindigkeit setzen
 * - ::cmActivate Aktivieren
 * - ::cmDeactivate Deaktivieren, keine Kollision mehr
 * - ::evHit Weiterleiten
 */
void PhysicsComponent::notify(EventMessage* message) {
    switch (message->event) {
    case cmApplyForce: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        thrust = posMessage->force;
        break;
    }
    case cmRotateTo: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        rotating = true;
        torque = posMessage->torque;
        rotationVector = posMessage->pos - body->GetPosition();
        break;
    }
    case cmStopRotating: {
        rotating = false;
        break;
    }
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        body->SetTransform(posMessage->pos, posMessage->rotation);
        body->SetLinearVelocity(posMessage->velocity);
        break;
    }
    case cmActivate: {
        body->SetEnabled(true);
        break;
    }
    case cmDeactivate: {
        body->SetEnabled(false);
        break;
    }
    case evHit: {
        notifyListeners(message);
        break;
    }
    }
    delete message;;
}

PhysicsComponent::PhysicsComponent(PhysicsSettings settings, Handle* handle)
    : Component(settings, handle) {

    world = settings.world;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = settings.pos;
    bodyDef.angle = settings.rotation;
    bodyDef.linearDamping = settings.linearDamping;
    bodyDef.angularDamping = settings.angularDamping;
    body = world->CreateBody(&bodyDef);

    assert(!settings.shapes.empty());

    /*
     * Shapes bzw. Fixtures zum Body hinzufügen
     */
    typename vector<b2Shape*>::iterator it = settings.shapes.begin();



    for (it; it != settings.shapes.end(); it++) {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = *it;
        fixtureDef.density = settings.density;
        fixtureDef.friction = settings.friction;
        fixtureDef.isSensor = false;
        fixtureDef.filter.categoryBits = settings.category;
        fixtureDef.filter.maskBits = settings.collidingWith;
        b2FixtureUserData data;
        data.pointer = (uintptr_t) handle;
        fixtureDef.userData = data;

        body->CreateFixture(&fixtureDef);
    }
    localCenter = body->GetLocalCenter();

    Event events[2] = {evMove, evHit};
    initializeEvents(events, 2);
}


PhysicsComponent::~PhysicsComponent() {
}
