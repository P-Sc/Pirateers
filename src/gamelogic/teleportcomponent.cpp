#include "teleportcomponent.h"

/**
 * @brief Spielt einen Sound ab. Versendet ::cmPlaySound
 * @param filename Dateiname
 */
void TeleportComponent::playSound(std::string filename) {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->event = cmPlaySound;
    soundMessage->file = filename;
    notifyListeners(soundMessage);
    delete soundMessage;
}


/**
 * @brief Erzeugt einen Lichtblitz. Versendet ::cmSpawnLight
 * @param size Durchmesser des Lichtblitzes
 * @param offset Versatz vom Spieler
 */
void TeleportComponent::spawnLight(float size, b2Vec2 offset) {
    EventLightMessage* lightMessage = new EventLightMessage;
    lightMessage->color = sf::Color(rand() % 50,
                                    200 + rand() % 50,
                                    200 + rand() % 50,
                                    100 + rand() % 150);
    lightMessage->delay = 0;
    lightMessage->duration = 0.5f;
    lightMessage->fadeDelay = 0.2f;
    lightMessage->size = size;
    lightMessage->pos = offset;
    lightMessage->pos += playerPos;
    notifyListeners(lightMessage);
    delete lightMessage;
}


/**
 * @brief Aktiviert/Deaktiviert Komponenten. Verschickt ::cmActivate oder ::cmDeactivate.
 * @param active Gibt an, ob aktiviert oder deaktiviert werden soll
 */
void TeleportComponent::setActive(bool active) {
    EventMessage* message = new EventMessage;

    if (active) {
        message->event = cmActivate;
    } else {
        message->event = cmDeactivate;
    }

    notifyListeners(message);
    delete message;
}


/**
 * @brief Versendet ::evTeleported
 */
void TeleportComponent::sendTeleportMessage() {
    EventMessage* message = new EventMessage(evTeleported);
    notifyListeners(message);
    delete message;
}

/**
 * @brief Versendet ::evPlayerSet oder ::evNoPlayerSet
 * @param playerSet Bei True ::evPlayerSet
 */
void TeleportComponent::sendPlayerSetMessage(bool playerSet) {
    EventMessage* message = new EventMessage;

    if (playerSet) {
        message->event = evPlayerSet;
    } else {
        message->event = evNoPlayerSet;
    }

    notifyListeners(message);
    delete message;
}


/**
 * @brief Aktualisiert Komponente.
 * @param dt Vergangene Zeit in ms
 */
void TeleportComponent::tick(float dt) {
    if (status == teleportingOut) {
        delay -= dt / 1000.f;
        flashThreshold += dt;
        int dice = rand() % 1000 + delay * 100.f;

        if (dice < (int) flashThreshold) {
            flashThreshold = 0;
            spawnLight(4 + rand() % 8, b2Vec2(rand() % 12 - 6, rand() % 12 - 6));
            playSound("flash.wav");
        }

        if (delay <= 0) {
            status = inTransit;
            spawnLight(30, b2Vec2(0, 0));
            playSound("teleport.wav");
            setActive(false);
            sendTeleportMessage();
            sendPlayerSetMessage(false);
        }
    } else if (status == teleportingIn) {
        delay -= dt / 1000.f;
        flashThreshold += dt;
        int dice = rand() % 3000;

        if (dice < (int) flashThreshold) {
            flashThreshold = 0;
            spawnLight(4 + rand() % 8, b2Vec2(rand() % 12 - 6, rand() % 12 - 6));
            playSound("flash.wav");
        }

        if (delay <= 0) {
            status = notTeleporting;
            spawnLight(30, b2Vec2(0, 0));
            playSound("teleport.wav");
            setActive(true);
            sendPlayerSetMessage(true);
            cooldown = maxCooldown;
        }
    } else if (status == notTeleporting) {
        cooldown = std::max(cooldown - dt / 1000.f, 0.f);
    }
}

/**
 * @copydoc Component::notify
 * - ::cmStartTeleport Startet den Teleport, falls noch kein cooldown besteht
 * - ::evMove Spielerposittion
 * - ::evAreaChanged Aktiviert den Teleport hinein
 */
void TeleportComponent::notify(EventMessage* message) {
    switch (message->event) {
    case cmStartTeleport: {
        if (cooldown == 0 && status != inTransit) {
            status = teleportingOut;
            delay = maxOutDelay;
            flashThreshold = 0;
        } else {
            playSound("menu_error.wav");
        }

        break;
    }

    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        playerPos = posMessage->center;
        break;
    }

    case evAreaChanged: {
        if (status == inTransit) {
            status = teleportingIn;
            delay = maxInDelay;
            flashThreshold = 0;
            playSound("transit.ogg");
        }

        break;
    }
    }
}

TeleportComponent::TeleportComponent(Settings settings, Handle* handle)
    : Component(settings, handle) {

    Event events[7] = {cmPlaySound, cmSpawnLight, evTeleported, cmActivate, cmDeactivate,
                       evNoPlayerSet, evPlayerSet
                      };
    initializeEvents(events, 7);
}
