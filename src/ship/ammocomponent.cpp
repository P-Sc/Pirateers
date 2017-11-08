#include "ammocomponent.h"
#include "graphics/graphicssystem.h"
#include "physics/physicssystem.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"


/**
 * @brief Signalisiert das Treffen eines Projektils.
 * @param p das Projektil, das getroffen hat.
 */
void AmmoComponent::reportHit(Projectile* p) {
    EventHitMessage* hitMessage = new EventHitMessage();
    hitMessage->damage = this->settings.damage;
    hitMessage->receiverId = p->targetHandle->id;
    hitMessage->pos = p->pos;
    physicsSystem->getEventManager()->sendMessage(hitMessage);
    //p->targetHandle->system->getEventManager()->sendMessage(hitMessage);
}

/**
 * @brief Signalisiert das Feuern der Kanone.
 */
void AmmoComponent::reportFire() {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->file = settings.soundSettings.filename;
    notifyListeners(soundMessage);
    delete soundMessage;

    EventMessage* shakeMessage = new EventMessage(cmShake);
    notifyListeners(shakeMessage);
    delete shakeMessage;

    EventMessage* energyMessage = new EventMessage(evEnergyUsed);
    energyMessage->value = settings.energyConsumption;
    notifyListeners(energyMessage);
    delete energyMessage;

}

/**
 * @brief Gibt zurück, ob die Komponente am feuern ist.
 * @return True, falls die Komponente feuert.
 */
bool AmmoComponent::isFiring() {
    return firing;
}


/**
 * @brief (De-)Aktiviert ein Projektil.
 * @param p Das Projektil.
 * @param isActive Gibt an, ob es aktiviert oder deaktiviert werden soll.
 */
void AmmoComponent::setVisible(Projectile* p, bool isActive) {
    Event event;

    if (isActive) {
        event = cmActivate;
    } else {
        event = cmDeactivate;
    }

    EventMessage* graphicsMessage = new EventMessage(event);
    graphicsMessage->gameSystemListener = false;
    graphicsMessage->receiverId = p->graphicsHandle->id;
    //graphicsSystem->getEventManager()->sendMessage(graphicsMessage);
    p->graphicsHandle->system->getEventManager()->sendMessage(graphicsMessage);

    EventMessage* lightMessage = new EventMessage(event);
    lightMessage->gameSystemListener = false;
    lightMessage->receiverId = p->lightHandle->id;
    //lightSystem->getEventManager()->sendMessage(lightMessage);
    p->lightHandle->system->getEventManager()->sendMessage(lightMessage);

}

/*
void AmmoComponent::setGraphicsSystem(GraphicsSystem* value) {
    graphicsSystem = value;
}
*/

/**
 * @brief Setzt das PhysicSystem.
 * @param value Das PhysicsSystem.
 *
 * Nötig für die RayCasts.
 */
void AmmoComponent::setPhysicsSystem(PhysicsSystem* value) {
    physicsSystem = value;
}


/**
 * @brief Aktualisiert Komponente
 * @param dt Zeit in ms
 */
void AmmoComponent::tick(float dt) {

    /*
     * Update every active Projectile
     */
    for (unsigned int i = activeProjectiles.size(); i-- > 0;) {
        activeProjectiles[i]->lifetime -= dt / 1000;

        if (activeProjectiles[i]->hit) {
            reportHit(activeProjectiles[i]);
            activeProjectiles[i]->hit = false;
            setVisible(activeProjectiles[i], false);
            idleProjectiles.push_back(activeProjectiles[i]);
            activeProjectiles.erase(activeProjectiles.begin() + i);
        } else if (activeProjectiles[i]->lifetime <= 0) {
            activeProjectiles[i]->hit = false;
            setVisible(activeProjectiles[i], false);
            idleProjectiles.push_back(activeProjectiles[i]);
            activeProjectiles.erase(activeProjectiles.begin() + i);
        } else {
            if (!activeProjectiles[i]->visible) {
                setVisible(activeProjectiles[i], true);
            }

            activeProjectiles[i]->step(dt);
            physicsSystem->getWorld()->RayCast(activeProjectiles[i], activeProjectiles[i]->pos,
                                               activeProjectiles[i]->nextPos);
        }
    }
}


/**
 * @brief Feuert, falls Kanone wieder schießen kann und genug Energie vorhanden ist.
 * @param dt Zeit in ms
 */
void AmmoComponent::fire(float dt) {
    idleDuration += dt / 1000.f;

    if (idleDuration >= firingGap && idleProjectiles.size() > 0
            && currentEnergy - settings.energyConsumption >= 0
            && currentEnergy / maxEnergy >= 0.1) {

        currentEnergy -= settings.energyConsumption;
        idleDuration = idleDuration - firingGap;

        Projectile* p = idleProjectiles.back();
        p->lifetime = maxProjectileLifetime;
        p->hit = false;
        (*dist)(*gen);
        float scatter = (*dist)(*gen);
        p->pos = spawningPos;
        p->nextPos = spawningPos;
        p->vel = b2Mul(b2Rot(spawningDir + scatter), b2Vec2(settings.velocity, 0)) + spawningVel;
        p->rotation = spawningDir - M_PI / 2.f;

        idleProjectiles.pop_back();
        activeProjectiles.push_back(p);
        reportFire();
    }
}

/**
 * @copydoc GameComponent::notify
 * - ::evMove Spawn-Position/-Geschwindigkeit aktualisieren
 * - ::cmOpenFire Feuer eröffnen
 * - ::cmCeaseFire Feuer einstellen
 * - ::evEnergyStatus Energiestatus aktualisieren
 * - ::cmUpgrade Waffe verbessern
 */
void AmmoComponent::notify(EventMessage *message) {
    switch(message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        spawningPos = posMessage->pos;
        spawningVel = posMessage->velocity;
        spawningDir = posMessage->rotation + M_PI / 2.f;
        break;
    }

    case cmOpenFire: {
        firing = true;
        idleDuration = firingGap;
        break;
    }

    case cmCeaseFire: {
        firing = false;
        idleDuration = 0.f;
        break;
    }

    case evEnergyStatus: {
        currentEnergy = message->value;
        maxEnergy = message->value2;
        break;
    }

    case cmUpgrade: {
        EventUpgradeMessage* upMessage = (EventUpgradeMessage*) message;
        if (upMessage->upgrade == "damage") {
            settings.damage += upMessage->value;
        } else if (upMessage->upgrade == "range") {
            settings.range += upMessage->value;
            requiresNewSize = true;
        } else if (upMessage->upgrade == "fire rate") {
            settings.rateOfFire += upMessage->value;
            requiresNewSize = true;
        } else if (upMessage->upgrade == "projectile velocity") {
            settings.velocity += upMessage->value;
            requiresNewSize = true;
        } else if (upMessage->upgrade == "scatter") {
            settings.scatter *= upMessage->value;
            delete dist;
            dist = new std::uniform_real_distribution<>(-M_PI * settings.scatter, M_PI * settings.scatter);
        }
        break;
    }

    case cmActivate: {
        settings.active = true;
        break;
    }
    case cmDeactivate: {
        settings.active = false;
        break;
    }
    }

    delete message;;
}


AmmoComponent::AmmoComponent(AmmoSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {

    r = new std::random_device;
    gen = new std::mt19937((*r)());
    dist = new std::uniform_real_distribution<>(-M_PI * settings.scatter, M_PI * settings.scatter);

    Event events[6] = {cmActivate, cmDeactivate, evHit, cmPlaySound, cmShake, evEnergyUsed};
    initializeEvents(events, 6);
}
