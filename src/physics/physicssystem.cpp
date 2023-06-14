#include "physicssystem.h"


b2World* PhysicsSystem::getWorld() {
    return world;
}

/**
 * @brief Body einer Komponente zurückgeben
 * @param id Die ID der Komponente
 * @return Der Body
 */
b2Body *PhysicsSystem::getBody(unsigned int id) {
    editLock.lock();
    b2Body* body = componentList[indices.get(id)].body;
    editLock.unlock();
    return body;
}


/**
 * @copydoc GameSystem::update
 * Aktualisiert Komponenten und versendet ::evMove
 */
void PhysicsSystem::update(float dt) {
    GameSystem::update(dt);
    world->Step(timeStep, velocityIterations, positionIterations);
    //world->Step(dt/1000.f*2.f, velocityIterations, positionIterations);

    EventPosMessage* message = new EventPosMessage();
    message->event = evMove;

    for (unsigned int i = 0; i < componentList.size(); i++) {
        if (componentList[i].body->IsEnabled()) {
            /*
             * Listener Position und Rotation senden
             */
            b2Vec2 localCenter = b2Mul(b2Rot(componentList[i].body->GetAngle()),
                                       componentList[i].localCenter);
            message->pos = componentList[i].body->GetPosition();
            message->velocity = componentList[i].body->GetLinearVelocity();
            message->center = message->pos + localCenter;
            message->rotation = componentList[i].body->GetAngle();
            componentList[i].notifyListeners(message);

            /*
             * Drehen
             */
            if (componentList[i].rotating) {
                b2Rot currentRotation = componentList[i].body->GetTransform().q;
                b2Vec2 currentVector = b2Mul(currentRotation, b2Vec2(0, 1));
                float dot = b2Dot(currentVector, componentList[i].rotationVector);
                float det = b2Cross(currentVector, componentList[i].rotationVector);

                float angle = atan2(det, dot);

                if (angle > M_PI * 0.2) {
                    angle = M_PI * 0.2;
                } else if (angle < -M_PI * 0.2) {
                    angle = -M_PI * 0.2;
                }

                //componentList[i].body->ApplyTorque(angle*componentList[i].torque, true);
                componentList[i].body->SetAngularVelocity(angle * componentList[i].torque);
            }

            /*
             * Antrieb
             */
            if (componentList[i].thrust != 0) {
                b2Vec2 forceVector = b2Mul(b2Rot(componentList[i].body->GetAngle()), b2Vec2(0, 1));
                forceVector *= componentList[i].thrust;
                b2Vec2 pointVec(componentList[i].body->GetWorldCenter());
                componentList[i].body->ApplyForce(forceVector, pointVec, true);
            }
        }
    }

    delete(message);
}


void PhysicsSystem::eraseComponent(unsigned int id) {
    editLock.lock();
    world->DestroyBody(componentList[indices.get(id)].body);
    editLock.unlock();
    GameSystem::eraseComponent(id);
}


Handle* PhysicsSystem::createComponent(PhysicsSettings settings) {
    settings.world = this->getWorld();
    return GameSystem::createComponent(settings);
}


PhysicsSystem::PhysicsSystem() : gravity(0.0f, 0.0f), world(new b2World(gravity)), GameSystem() {

}
/*
PhysicsSystem::~PhysicsSystem() {
    editLock.lock();

    for (typename std::vector<PhysicsComponent>::iterator it = componentList.begin();
            it != componentList.end(); it++) {
        if (it->alive) {
            world.DestroyBody(it->body);
        }
    }

    editLock.unlock();
}
*/
