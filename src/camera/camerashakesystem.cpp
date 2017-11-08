#include "camerashakesystem.h"

/**
 * @brief Gibt die derzeitige Verschiebung der Kamera an
 * @return die Verschiebung
 */
sf::Vector2f CameraShakeSystem::getShakeOffset() {
    return totalOffset;
}


/**
 * @copydoc GameSystem::update
 *
 * Aktualisiert Komponenten und summiert den Versatz.
 */
void CameraShakeSystem::update(float dt) {
    GameSystem::update(dt);
    totalOffset.x = 0;
    totalOffset.y = 0;

    for (unsigned int i = 0; i < componentList.size(); i++) {
        componentList[i].tick(dt);

        if (componentList[i].isShaking()) {
            totalOffset += componentList[i].getOffset() * scale;
        }
    }
}

/**
 * @copydoc GameSystem::notify
 * - ::evCameraChanged Aktualisiert den Zoom-Faktor
 */
void CameraShakeSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        scale = cameraMessage->scale;
        break;
    }
    }

    delete message;;
}

/**
 * @copydoc GameSystem::createComponent
 */
Handle* CameraShakeSystem::createComponent(CameraShakeSettings settings) {
    return GameSystem::createComponent(settings);
}
