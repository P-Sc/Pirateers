#include "aisystem.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @brief Setzt die verbesserte Zielfähigkeit bei allen Komponenten
 * @see AIComponent::setSuperiourAim
 */
void AISystem::setSuperiourAim(bool superiourAim) {
    this->superiourAim = superiourAim;
}

/**
 * @deprecated Ist unbenutzt
 */
void AISystem::setCombatStatus(bool playerInCombat) {
    if (this->playerInCombat != playerInCombat) {
        // TODO: Nachricht versenden!
    }

    this->playerInCombat = playerInCombat;
}

/**
 * @copydoc GameSystem::update
 *
 * Aktualisiert alle Komponenten. Aktualisiert alle 500ms die Zustände. Zeichnet Debug-Information
 */
void AISystem::update(float dt) {
    GameSystem::update(dt);

    stateUpdateThreshold += dt;
    bool inCombat = false;

    if (playerSet) {
        if (stateUpdateThreshold >= STATE_UPDATE_INTERVAL) {
            for (unsigned int i = 0; i < componentList.size(); i++) {
                componentList[i].setPlayerPos(playerPos, playerVel);
                componentList[i].updateState();
                componentList[i].update();

                if (!inCombat) {
                    inCombat = componentList[i].isInCombat();
                }

                if (componentList[i].isDead()) {
                    eraseComponent(componentList[i].getId());
                }
            }

            stateUpdateThreshold = 0;
        } else {
            for (unsigned int i = 0; i < componentList.size(); i++) {
                componentList[i].setPlayerPos(playerPos, playerVel);
                componentList[i].update();

                if (!inCombat) {
                    inCombat = componentList[i].isInCombat();
                }

                if (componentList[i].isDead()) {
                    eraseComponent(componentList[i].getId());
                }
            }
        }
    }

    if (drawDebug) {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            window->draw(componentList[i].stateText);
            window->draw(componentList[i].aimText);
            window->draw(componentList[i].targetShape);
            window->draw(componentList[i].targetLine, 2, sf::Lines);
        }
    }

    if (aimSettingsChanged) {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            componentList[i].setSuperiourAim(this->superiourAim);
        }
        aimSettingsChanged = false;
    }
}

Handle* AISystem::createComponent(AISettings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    editLock.lock();
    getComponent(handle->id)->stateText.setFont(debugFont);
    getComponent(handle->id)->aimText.setFont(debugFont);
    getComponent(handle->id)->setSuperiourAim(this->superiourAim);
    editLock.unlock();
    return handle;
}

/**
 * @copydoc GameSystem::notify
 * - ::evMove Spielerposition
 * - ::evKeyPressed Für Debug
 * - ::evPlayerSet Aktiviert Komponenten
 * - ::evNoPlayerSet Deaktiviert Komponenten
 */
void AISystem::notify(EventMessage* message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        playerPos = posMessage->center;
        playerVel = posMessage->velocity;
        break;
    }

    case evKeyPressed: {
        EventKeyMessage* keyMessage = (EventKeyMessage*) message;

        if (keyMessage->key == Keyboard::F3) {
            if (drawDebug) {
                drawDebug = false;
            } else {
                drawDebug = true;
            }
        } else if (keyMessage->key == Keyboard::F4) {
            setSuperiourAim(!superiourAim);
            aimSettingsChanged = true;
        }
        break;
    }

    case evPlayerSet: {
        playerSet = true;
        break;
    }

    case evNoPlayerSet: {
        playerSet = false;
        for (int i = 0; i < componentList.size(); i++) {
            componentList[i].setState(State::idling);
        }
        break;
    }
    }

    delete message;;
}

AISystem::AISystem(sf::RenderWindow* window) : window(window) {
    debugFont.loadFromFile("../resources/FreeMono.otf");
}
