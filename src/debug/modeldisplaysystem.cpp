#include <SFML/Graphics.hpp>

#include "modeldisplaysystem.h"



void ModelDisplaySystem::setDisplay(bool value) {
    display = value;
}


/**
 * @copydoc GameSystem::update
 *
 * Zeichnet jedes ModelDisplayComponent.
 */
void ModelDisplaySystem::update(float dt) {
    GameSystem::update(dt);

    if (display) {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            if (componentList[i].visible) {
                for (auto &polygon : componentList[i].polygons) {
                    window->draw(polygon);
                }

                for (auto &circle : componentList[i].circles) {
                    window->draw(circle);
                }

                for (auto &rect : componentList[i].lines) {
                    window->draw(rect);
                }
            }
        }
    }
}

void ModelDisplaySystem::notify(EventMessage * message) {
    switch (message->event) {
    case evKeyPressed: {
        EventKeyMessage * keyMessage = (EventKeyMessage*) message;

        if (keyMessage->key == Keyboard::F2) {
            display = !display;
        }

        delete keyMessage;
        break;
    }

    default: {
        delete message;
        break;
    }
    }
}

Handle* ModelDisplaySystem::createComponent(ModelSettings settings) {
    return GameSystem::createComponent(settings);
}

ModelDisplaySystem::ModelDisplaySystem(sf::RenderWindow * window) {
    this->window = window;
}
