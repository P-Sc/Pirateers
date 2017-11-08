#include "aicomponent.h"

/**
 * @brief Berechnet Distanz zu einem Punkt
 * @param pos Der Punkt
 * @return Die Distanz
 */
float AIComponent::distanceTo(b2Vec2& pos) {
    b2Vec2 dir = pos - this->pos;
    return dir.Length();
}


/**
 * @brief Zielt auf den Spieler. Verschickt eine ::cmAimTo-Nachricht.
 */
void AIComponent::aim() {
    EventPosMessage* posMessage = new EventPosMessage;
    posMessage->event = cmAimAt;
    float pTime = distanceTo(playerPos) / settings.projectileVelocity;
    posMessage->pos = playerPos - b2Vec2(vel.x * pTime, vel.y * pTime);

    if (superiourAim) {
        posMessage->pos += b2Vec2(playerVel.x * pTime, playerVel.y * pTime);
    }

    notifyListeners(posMessage);
    delete posMessage;
}

/**
 * @brief Rotiert zu einem Punkt. Verschickt eine ::cmRotateTo-Nachricht
 * @param pos Der Punkt.
 */
void AIComponent::rotateTo(b2Vec2& pos) {
    EventPosMessage* posMessage = new EventPosMessage;
    posMessage->event = cmRotateTo;
    posMessage->pos = pos;
    notifyListeners(posMessage);
    delete posMessage;
}

/**
 * @brief Hört auf zu rotieren. Verschickt eine ::cmStopRotating-Nachricht
 */
void AIComponent::stopRotating() {
    EventMessage* message = new EventMessage(cmStopRotating);
    notifyListeners(message);
    delete message;
}

/**
 * @brief Setzt die Schubkraft
 * @param percentage Prozent
 */
void AIComponent::powerEngines(float percentage) {
    EventMessage* message = new EventMessage(cmPowerEngines);
    message->value = percentage;
    notifyListeners(message);
    delete message;
}

/**
 * @brief Setzt den Feuermodus (an/aus). Verschickt ::cmOpenFire oder ::cmCeaseFire
 * @param firing Feuert, falls True
 */
void AIComponent::setFireMode(bool firing) {
    Event event;

    if (firing) {
        event = cmOpenFire;
        isFiring = true;
    } else {
        event = cmCeaseFire;
        isFiring = false;
    }

    EventMessage* message = new EventMessage(event);
    notifyListeners(message);
    delete message;
}


/**
 * @brief Setzt einen Zustand und setzt die zugehörigen Einstellungen
 * @param newState Der neue Zustand
 */
void AIComponent::setState(State newState) {
    switch (newState) {
    case hunting: {
        setFireMode(true);
        stateText.setString("Hunting");
        targetShape.setFillColor(sf::Color::Green);
        targetLine[0].color = sf::Color::Green;
        targetLine[1].color = sf::Color::Green;
        powerEngines(1.f);
        break;
    }

    case retreating: {
        setFireMode(false);
        stateText.setString("Retreating");
        stopRotating();
        targetShape.setFillColor(sf::Color::Transparent);
        targetLine[0].color = sf::Color::Transparent;
        targetLine[1].color = sf::Color::Transparent;
        powerEngines(1.f);
        break;
    }

    case circling: {
        setFireMode(true);
        stateText.setString("Circling");
        targetShape.setFillColor(sf::Color::Green);
        targetLine[0].color = sf::Color::Green;
        targetLine[1].color = sf::Color::Green;
        powerEngines(1.f);
        break;
    }

    case flanking: {
        setFireMode(true);
        stateText.setString("Flanking");
        targetShape.setFillColor(sf::Color::Green);
        targetLine[0].color = sf::Color::Green;
        targetLine[1].color = sf::Color::Green;
        powerEngines(1.f);
        break;
    }

    case idling: {
        setFireMode(false);
        stateText.setString("Idling");
        stopRotating();
        targetShape.setFillColor(sf::Color::Transparent);
        targetLine[0].color = sf::Color::Transparent;
        targetLine[1].color = sf::Color::Transparent;
        powerEngines(0.f);
        break;
    }
    }

    state = newState;
}

/**
 * @brief Gibt an, ob Komponente tot ist
 * @return True, falls tot.
 */
bool AIComponent::isDead() {
    return dead;
}

/**
 * @brief Aktualisiert den Zustand. Überprüft Bedingungen und wechselt den Zustand, falls
 *        die richtigen Bedingungen gegeben sind.
 *
 * Bedingungen sind spezifisch für jeden AIType/Zustand
 */
void AIComponent::updateState() {
    switch (settings.type) {
    case AISettings::fighter: {
        switch (state) {
        case hunting: {
            //if ( ((float)energy) / maxEnergy < 0.1f || ((float)shield) / maxShield < 0.1f
            //        || distanceTo(playerPos) < settings.combatRadius * 1.2f) {
            if (!isFiring && distanceTo(playerPos) < 0.5f * settings.weaponRange) {
                setFireMode(true);
            } else if ( distanceTo(playerPos) < settings.combatRadius * 1.2f || ((float)energy) / maxEnergy < 0.1f) {
                setState(retreating);
            } else if (!inCombat) {
                setState(idling);
            }

            break;
        }

        case retreating: {
            if ( ((float)energy) / maxEnergy > 0.8f && distanceTo(playerPos)
                    > 0.6f * settings.weaponRange) {
                setState(hunting);
                setFireMode(false);
            } else if (!inCombat) {
                setState(idling);
            }

            break;
        }

        case idling: {
            if (inCombat) {
                setState(hunting);
            }

            break;
        }
        }
    }

    case AISettings::drone: {
        switch (state) {
        case circling: {
            //if ( ((float)energy) / maxEnergy < 0.1f || ((float)shield) / maxShield < 0.1f
            //        || distanceTo(playerPos) < settings.combatRadius * 1.2f) {
            if (!inCombat) {
                setState(idling);
            }

            break;
        }

        case idling: {
            if (inCombat) {
                setState(circling);
            }

            break;
        }
        }

        break;
    }

    case AISettings::freighter: {
        switch (state) {
        case retreating: {
            if (!inCombat) {
                setState(idling);
            }

            break;
        }

        case idling: {
            if (inCombat) {
                setState(retreating);
                setFireMode(true);
            }

            break;
        }
        }

        break;
    }

    case AISettings::gunship: {
        switch (state) {
        case flanking: {
            if (!inCombat) {
                setState(idling);
            }

            break;
        }

        case idling: {
            if (inCombat) {
                setState(flanking);
            }

            break;
        }
        }

        break;
    }
    }
}


/**
 * @brief Führt Zustände aus
 */
void AIComponent::update() {
    switch (state) {
    case hunting: {
        b2Vec2 dir = pos - playerPos;
        b2Vec2 offset(-dir.y, dir.x);
        offset.Normalize();
        offset *= settings.combatRadius;
        b2Vec2 reverseOffset(-offset.x, -offset.y);

        if (distanceTo(reverseOffset) < distanceTo(offset)) {
            targetPos = reverseOffset;
        } else {
            targetPos = offset;
        }

        targetPos += playerPos;

        rotateTo(targetPos);
        aim();
        targetShape.setPosition(targetPos.x * 30.f, targetPos.y * 30.f);
        break;
    }

    case circling: {
        //b2Vec2 dir = playerPos - pos;
        b2Vec2 dir = pos - playerPos;
        dir.Normalize();
        b2Rot targetRot;

        if (b2Dot(dir, rot) > 0) {
            targetRot.Set(M_PI * 0.15);
        } else {
            targetRot.Set(M_PI * -0.15);
        }

        dir = b2Mul(targetRot, dir);
        dir *= settings.combatRadius;
        targetPos = playerPos + dir;
        rotateTo(targetPos);
        aim();
        targetShape.setPosition(targetPos.x * 30.f, targetPos.y * 30.f);
        break;
    }

    case retreating: {
        aim();
        break;
    }

    case flanking: {
        b2Vec2 vecToPlayer = targetPos - playerPos;
        b2Vec2 vecToThis = targetPos - pos;

        if (vecToPlayer.Length() > settings.combatRadius || vecToThis.Length() < 5) {
            targetPos = b2Mul(b2Rot((rand() % (int) (2 * M_PI * 100)) / 100.f),
                              b2Vec2(0, rand() % (int) settings.combatRadius));
            targetPos += playerPos;
            rotateTo(targetPos);
        }

        aim();
        targetShape.setPosition(targetPos.x * 30.f, targetPos.y * 30.f);
        break;
    }
    }

    targetLine[0].position = sf::Vector2f(pos.x * 30.f, pos.y * 30.f);
    targetLine[1].position = targetShape.getPosition();
    stateText.setPosition(pos.x * 30.f + 100, pos.y * 30.f + 100);
    aimText.setPosition(pos.x * 30.f + 100, pos.y * 30.f + 140);
}


/**
 * @brief Aktualisiert die Spielerposition
 * @param playerPos Spielerposition
 * @param playerVel Spielergeschwindigkeit
 */
void AIComponent::setPlayerPos(b2Vec2& playerPos, b2Vec2& playerVel) {
    this->playerPos = playerPos;
    this->playerVel = playerVel;

    if (distanceTo(playerPos) <= settings.sightRange) {
        inCombat = true;
    } else {
        inCombat = false;
    }
}

/**
 * @brief Stellt verbesserte Trefferfähigkeit an/aus
 *
 * Falls angeschaltet, berechnet die KI die Geschwindigkeit des Spielers mit ein
 */
void AIComponent::setSuperiourAim(bool superiourAim) {
    this->superiourAim = superiourAim;

    if (superiourAim) {
        aimText.setString("Superiour accuracy");
        aimText.setColor(sf::Color::Red);
    } else {
        aimText.setString("Normal accuracy");
        aimText.setColor(sf::Color::Green);
    }
}


bool AIComponent::isInCombat() {
    return inCombat;
}

void AIComponent::notify(EventMessage* message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        pos = posMessage->center;
        rot = b2Mul(b2Rot(posMessage->rotation), b2Vec2(1, 0));
        vel = posMessage->velocity;
        break;
    }

    case evShield: {
        EventShieldMessage* shieldMessage = (EventShieldMessage*) message;
        hull = shieldMessage->hull;
        maxHull = shieldMessage->maxHull;
        shield = shieldMessage->shield;
        maxShield = shieldMessage->maxShield;
        break;
    }

    case evEnergyStatus: {
        energy = message->value;
        maxEnergy = message->value2;
        break;
    }

    case evDestroyed: {
        //delete handle;
        dead = true;
        break;
    }
    }

    delete message;;
}

AIComponent::AIComponent(AISettings settings, Handle* handle)
    : settings(settings), targetShape(10, 4), Component(settings, handle) {

    stateText.setCharacterSize(30);
    stateText.setColor(sf::Color::Green);
    stateText.setString("Idling");
    aimText.setCharacterSize(30);
    aimText.setColor(sf::Color::Green);
    aimText.setString("Normal Aiming");
    targetShape.setOrigin(5, 5);
    targetLine[0].color = sf::Color::Green;
    targetLine[1].color = sf::Color::Green;

    Event events[6] = {cmPowerEngines, cmRotateTo, cmStopRotating, cmAimAt, cmOpenFire, cmCeaseFire};
    initializeEvents(events, 6);

}
