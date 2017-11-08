#include "lightsystem.h"
//#include <algorithm>
//#include <SFML/Graphics/VertexArray.hpp>
#include "graphics/textures.h"


/**
 * @brief Liste an zu erstellenden Lichtern verarbeiten.
 */
void LightSystem::processCreationQueue() {
    std::vector<EventLightMessage*>::iterator it = creationQueue.begin();
    for (; it != creationQueue.end(); it++) {
        EventLightMessage* lightMessage = (*it);
        LightSettings lightSettings;
        lightSettings.color = lightMessage->color;
        lightSettings.pos = lightMessage->pos;
        lightSettings.size = lightMessage->size;
        createTemporaryComponent(lightSettings, lightMessage->duration, lightMessage->delay,
                                 lightMessage->fadeDelay);
        delete lightMessage;
    }
    creationQueue.clear();
}

/**
 * @brief Tempöräres Licht erstellen. Wird nach dem abklingen gelöscht.
 * @param settings Die Einstellungen für das Licht
 * @param duration Dauer in s
 * @param delay Verzögerung bis Licht auftaucht in s
 * @param fadeDelay Verzögerung, bis Anfang des Ausblendens
 */
void LightSystem::createTemporaryComponent(LightSettings settings, float duration, float delay,
        float fadeDelay) {
    // TODO: nicht für Multi-Threading geeignet
    Handle* tempHandle = GameSystem::createComponent(settings);
    getComponent(tempHandle->id)->duration = duration;
    getComponent(tempHandle->id)->delay = delay;
    getComponent(tempHandle->id)->fadeDelay = fadeDelay;
    getComponent(tempHandle->id)->fadeDuration = std::max(duration - fadeDelay, 0.f);
}

sf::RenderTexture& LightSystem::getLightMap() {
    return lightMap;
}

/**
 * @copydoc GameSystem::update
 * Aktualisiert Komponenten. Löscht abgeklungene Lichter.
 */
void LightSystem::update(float dt) {
    GameSystem::update(dt);

    processCreationQueue();
    lightMap.clear();
    lightMap.setView(cameraView);
    sf::RenderStates renderState(sf::BlendAdd);

    int deleted = 0;
    for (unsigned int i = 0; i < componentList.size(); i++) {
        LightSettings& settings = componentList[i].getSettings();

        if (settings.active) {
            /*
             * Löschen, falls Licht abgeklungen
             */
            if (componentList[i].tick(dt)) {
                deleted++;
                eraseComponent(componentList[i].getId());
            } else {
                lightMap.draw(componentList[i].light, renderState);
            }
        }
    }

    lightMap.display();
}

/**
 * @copydoc GameSystem::notify
 * - ::evCameraChanged LightMap-Position aktualisieren
 * - ::evWindowResized LightMap-Größe aktualisieren
 * - ::cmSpawnLight Temporäres Licht erstellen
 */
void LightSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        cameraView.setCenter(cameraMessage->center.x * resolutionFactor,
                             cameraMessage->center.y * resolutionFactor);
        cameraView.setSize(cameraMessage->size.x * resolutionFactor,
                           cameraMessage->size.y * resolutionFactor);
        break;
    }

    case evWindowResized: {
        EventResizedMessage* resizedMessage = (EventResizedMessage*) message;
        lightMap.create(resizedMessage->size.x * resolutionFactor,
                        resizedMessage->size.y * resolutionFactor);
        break;
    }

    case cmSpawnLight: {
        EventLightMessage* lightMessage = (EventLightMessage*) message;
        //EventLightMessage* lightMessageCopy = (EventLightMessage*) MessageCloner::cloneMessage(message);
        creationQueue.push_back(lightMessage);
        return;
    }
    }

    delete message;;
}

Handle* LightSystem::createComponent(LightSettings settings) {
    return GameSystem::createComponent(settings);
}

LightSystem::LightSystem(sf::RenderWindow* window) : window(window) {
    sf::Texture& texture = Textures::get("light_big.png");
    light.setTexture(texture);
    light.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    lightMap.create(1200 * resolutionFactor, 800 * resolutionFactor);
}
