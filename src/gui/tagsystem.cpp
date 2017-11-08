#include "tagsystem.h"
#include <SFML/Graphics.hpp>
#include "graphics/textures.h"

/**
 * @brief Pfeilrotation berechnen
 * @param shipPos Position des Schiffes
 * @return Nötige Rotation für den Pfeil
 */
float TagSystem::getArrowAngle(sf::Vector2f shipPos) {
    sf::Vector2f dir = shipPos - cameraCenter;
    return (atan2(dir.y, dir.x) / M_PI) * 180 + 90;
}

/**
 * @brief Schiffsposition auf Kamerarand projezieren
 * @param shipPos Das Schiff
 * @param borderOffset Abstand zum Kamerarand (positiv = nach innen)
 * @return Die projezierte Position
 */
sf::Vector2f TagSystem::getArrowPos(sf::Vector2f shipPos, float borderOffset) {
    sf::Vector2f arrowPos = shipPos;
    arrowPos.x = std::max(arrowPos.x, cameraBounds.left + borderOffset);
    arrowPos.x = std::min(arrowPos.x, cameraBounds.left + cameraBounds.width - borderOffset);
    arrowPos.y = std::max(arrowPos.y, cameraBounds.top + borderOffset);
    arrowPos.y = std::min(arrowPos.y, cameraBounds.top + cameraBounds.height - borderOffset);
    return arrowPos;
}


/**
 * @copydoc GameSystem::update
 * Komponenten aktualisieren und zeichnen
 */
void TagSystem::update(float dt) {
    GameSystem::update(dt);

    for (unsigned int i = 0; i < componentList.size(); i++) {
        if (componentList[i].visible) {
            window->draw(componentList[i].borderRight);
            window->draw(componentList[i].borderTopRight);
            window->draw(componentList[i].borderBottomRight);
            window->draw(componentList[i].borderLeft);
            window->draw(componentList[i].borderTopLeft);
            window->draw(componentList[i].borderBottomLeft);
            window->draw(componentList[i].hullBackgroundBar);
            window->draw(componentList[i].hullBorderBar);
            window->draw(componentList[i].hullBar);
            window->draw(componentList[i].shieldBackgroundBar);
            window->draw(componentList[i].shieldBorderBar);
            window->draw(componentList[i].shieldBar);
            window->draw(componentList[i].energyBackgroundBar);
            window->draw(componentList[i].energyBorderBar);
            window->draw(componentList[i].energyBar);

            if (!cameraBounds.contains(componentList[i].borderLeft.getPosition())
                    && !cameraBounds.contains(componentList[i].borderRight.getPosition())) {

                sf::Vector2f shipPos = componentList[i].borderLeft.getPosition()
                                       + 0.5f * (componentList[i].borderLeft.getPosition()
                                                 - componentList[i].borderRight.getPosition());

                if (componentList[i].arrow.getScale() != sf::Vector2f(scale, scale)) {
                    componentList[i].arrow.setScale(scale, scale);
                }

                componentList[i].arrow.setRotation(getArrowAngle(shipPos));
                float offset = componentList[i].arrow.getGlobalBounds().width * 0.3;
                componentList[i].arrow.setPosition(getArrowPos(shipPos,
                                                   offset));
                window->draw(componentList[i].arrow);
            }
        }
    }
}


/**
 * @copydoc GameSystem::notify
 * - ::evCameraChanged Kameraposition und -skalierung anpassen
 */
void TagSystem::notify(EventMessage *message) {
    switch (message->event) {
    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        cameraBounds.left = (cameraMessage->center.x - cameraMessage->size.x / 2);
        cameraBounds.top = (cameraMessage->center.y - cameraMessage->size.y / 2);
        cameraBounds.width = cameraMessage->size.x;
        cameraBounds.height = cameraMessage->size.y;
        cameraCenter.x = cameraMessage->center.x;
        cameraCenter.y = cameraMessage->center.y;
        scale = cameraMessage->scale * arrowScale;
        break;
    }

    }

    delete message;;
}

Handle *TagSystem::createComponent(TagSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    editLock.lock();

    componentList[indices.get(handle->id)].arrow.setTexture(arrowTexture);
    componentList[indices.get(handle->id)].arrow.setColor(settings.color);
    componentList[indices.get(handle->id)].arrow.setOrigin(arrowTexture.getSize().x / 2.f,
            arrowTexture.getSize().y / 2.f);
    componentList[indices.get(handle->id)].arrow.scale(arrowScale, arrowScale);
    editLock.unlock();
    return handle;
}

TagSystem::TagSystem(sf::RenderWindow *window)
    : window(window), arrowTexture(Textures::get("gui/arrow.png")) {
}
