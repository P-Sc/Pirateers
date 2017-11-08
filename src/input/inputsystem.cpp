#include "inputsystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "base/settings.h"


/**
 * @brief Aktuelle mauskoordinaten in EventMouseMessage setzen
 * @param message Die Nachricht
 * @param x X-Position (SFML-Koordinaten)
 * @param y Y-Position (SFML-Koordinaten)
 */
void InputSystem::enterMouseCoordinates(EventMouseMessage *message, int x, int y) {
    //message->x = x;
    //message->y = y;
    message->sfScreenPos.Set(x,y);
    //message->relX = ((float)x)/windowWidth;
    //message->relY = ((float)y)/windowHeight;
    message->sfRelScreenPos.Set(((float)x)/windowWidth, ((float)y)/windowHeight);
}


Handle* InputSystem::createComponent(Settings settings) {
    return GameSystem::createComponent(settings);
}


/**
 * @copydoc GameSystem::update
 * Verarbeitet und verschickt Eingaben
 */
void InputSystem::update(float dt) {
    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed: {
            EventMessage* message = new EventMessage(evWindowClosed);
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        case sf::Event::MouseWheelScrolled: {
            EventMouseMessage* message = new EventMouseMessage(evMouseWheelScrolled);
            message->scroll = event.mouseWheelScroll.delta;
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        case sf::Event::MouseMoved: {
            EventMouseMessage* message = new EventMouseMessage(evMouseMoved);
            enterMouseCoordinates(message, event.mouseMove.x, event.mouseMove.y);
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        case sf::Event::MouseButtonPressed: {
            EventMouseMessage* message = new EventMouseMessage(evMouseButtonPressed);
            message->button = event.mouseButton.button;
            enterMouseCoordinates(message, event.mouseButton.x, event.mouseButton.y);
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        case sf::Event::MouseButtonReleased: {
            EventMouseMessage* message = new EventMouseMessage(evMouseButtonReleased);
            message->button = event.mouseButton.button;
            enterMouseCoordinates(message, event.mouseButton.x, event.mouseButton.y);
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        case sf::Event::Resized: {
            EventResizedMessage* message = new EventResizedMessage();
            windowWidth = event.size.width;
            windowHeight = event.size.height;
            //message->width = event.size.width;
            //message->height = event.size.height;
            message->size.Set(event.size.width, event.size.height);
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        case sf::Event::KeyPressed: {
            EventKeyMessage* message = new EventKeyMessage();
            message->event = evKeyPressed;
            message->key = event.key.code;
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        case sf::Event::KeyReleased: {
            EventKeyMessage* message = new EventKeyMessage();
            message->event = evKeyReleased;
            message->key = event.key.code;
            componentList[0].notifyListeners(message);
            delete message;
            break;
        }
        }
    }

    /*
    EventKeyMessage* message = new EventKeyMessage();
    message->event = evKeyPressed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        message->left = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        message->right = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        message->up = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        message->down = true;

    componentList[0].notifyListeners(message);
    */
    //delete(message);
}

InputSystem::InputSystem(sf::RenderWindow* window) : GameSystem() {
    Settings settings;
    this->window = window;
    windowWidth = window->getSize().x;
    windowHeight = window->getSize().y;
    singleton = GameSystem::createComponent(settings);
}
