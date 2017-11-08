#include "graphicssystem.h"
#include "graphics/textures.h"
#include "exceptions/fileopenerror.h"
#include <cstdlib>

// DEBUG
#include <iostream>

const int initWindowWidth = 1200;
const int initWindowHeight = 800;

/**
 * @brief Ermittelt die Frames pro Sekunde und zeigt sie im Fenstertitel an
 */
void GraphicsSystem::displayFPS(float dt) {
    timeElapsed += dt;

    if( timeElapsed >= 1000.f) {
        fps = frameCount;
        frameCount = 0;
        timeElapsed = ((int) timeElapsed) % 1000;

        sprintf(c, "FPS: %d", fps);
        std::string string(c);
        window->setTitle(string);
    }

    frameCount++;
}

/**
 * @brief Zeichnet alle jedes GraphicsComponent
 */
void GraphicsSystem::update(float dt) {
    GameSystem::update(dt);
    lightShader.setParameter("u_texture", sf::Shader::CurrentTexture);
    lightShader.setParameter("u_lightmap", lightMap.getTexture());
    lightShader.setParameter("resolution", sf::Vector2f(window->getSize().x,
                             window->getSize().y));
    lightShader.setParameter("intensity", 150.f);
    sf::Vector2f uShift(1.f / window->getSize().x, 1.f / window->getSize().y);
    uShift *= blurFactor / scrollFactor;
    lightShader.setParameter("uShift", uShift);

    for (unsigned int layer = 0; layer < LAYER_COUNT; layer++) {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            if (componentList[i].isVisible(layer)) {
                if (componentList[i].usesShader()) {
                    window->draw(componentList[i].sprite, &lightShader);
                } else {
                    window->draw(componentList[i].sprite);
                }
            }
        }
    }

    displayFPS(dt);
}


/**
 * @copydoc GameSystem::notify
 *
 * Erkannte Events:
 *  - ::evWindowClosed Löscht alle Komponenten
 *  - ::evCameraChanged Übernimmt den Zoom-Faktor
 */
void GraphicsSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evWindowClosed: {
        editLock.lock();
        componentList.clear();
        window->setMouseCursorVisible(true);
        window->close();
        editLock.unlock();
        break;
    }

    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        scrollFactor = cameraMessage->scale;
        break;
    }
    }

    delete message;;
}


/**
 * @copydoc GameSystem::createComponent
 */
Handle* GraphicsSystem::createComponent(GraphicsSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    editLock.lock();
    GraphicsComponent* component = getComponent(handle->id);
    component->setVisible(true);
    std::string textureName = component->getTextureName();
    component->sprite.setTexture(Textures::get(textureName));
    sf::Vector2u uSize = component->sprite.getTexture()->getSize();
    sf::Vector2f size(uSize.x, uSize.y);
    component->sprite.setOrigin(0.5f * size);
    component->sprite.scale(settings.scale, settings.scale);
    editLock.unlock();
    return handle;
}



/**
 * @brief Gibt zurück, ob das Anzeigefenster noch offen ist
 * @return true, falls das Fenster offen ist.
 */
bool GraphicsSystem::isOpen() {
    return window->isOpen();
}



GraphicsSystem::GraphicsSystem(sf::RenderWindow * window, sf::RenderTexture& lightMap)
    : lightMap(lightMap) {

    this->window = window;
    lightShader.loadFromFile("../resources/light_low_res.frag", sf::Shader::Fragment);
}
