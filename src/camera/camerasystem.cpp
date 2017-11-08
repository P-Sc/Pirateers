#include "camerasystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "graphics/textures.h"
#include "camera/camerashakesystem.h"

const int initWindowWidth = 1200;
const int initWindowHeight = 800;

/**
 * @brief Zoomt heran/heraus
 * @param scroll Der Zoom-Faktor. Relativ zum derzeitigen Faktor.
 */
void CameraSystem::zoom(float scroll) {
    if (scroll < 0) {
        playerView.zoom(1.05f);
        cursor.scale(1.05f, 1.05f);
        scrollFactor *= 1.05f;
        mousePos.x *= 1.05f;
        mousePos.y *= 1.05f;
    } else if (scroll > 0) {
        playerView.zoom(0.95f);
        cursor.scale(0.95f, 0.95f);
        scrollFactor *= 0.95f;
        mousePos.x *= 0.95f;
        mousePos.y *= 0.95f;
    } else {
        return;
    }

    window->setView(playerView);
}


/**
 * @brief Zeichnet den Cursor
 */
void CameraSystem::drawCursor() {
    const sf::Vector2f center = playerView.getCenter();
    const sf::Vector2f size = playerView.getSize();
    cursor.setPosition(center.x - size.x / 2 + mousePos.x,
                       center.y - size.y / 2 + mousePos.y);
    window->draw(cursor);

}

Handle *CameraSystem::createComponent(Settings settings) {
    return singleton;
}


void CameraSystem::update(float dt) {
    GameSystem::update(dt);

    /*
     * Kamera-Update
     */
    sf::Vector2i tmp = sf::Mouse::getPosition(*window);
    mousePos = sf::Vector2f(tmp.x, tmp.y) * scrollFactor;
    sf::Vector2f mouseOffset = playerView.getSize() * 0.5f - sf::Vector2f(mousePos.x, mousePos.y);
    mouseOffset *= mouseFollowingFactor;
    interpolatedCenter += ((playerPos - mouseOffset) - interpolatedCenter) * linearInterpolationFactor;
    sf::Vector2f finalCenter = interpolatedCenter + cameraShakeSystem.getShakeOffset();
    playerView.setCenter(finalCenter);
    window->setView(playerView);

    /*
     * Sende evCameraChanged
     */
    sf::Vector2f relCameraOffset = finalCenter - playerPos;
    relCameraOffset.x = relCameraOffset.x / playerView.getSize().x;
    relCameraOffset.y = relCameraOffset.y / playerView.getSize().y;
    EventCameraMessage* cameraMessage = new EventCameraMessage();
    cameraMessage->center.Set(finalCenter.x, finalCenter.y);
    cameraMessage->size.Set(playerView.getSize().x, playerView.getSize().y);
    cameraMessage->relOffset.Set(relCameraOffset.x, relCameraOffset.y);
    cameraMessage->scale = scrollFactor;
    componentList[0].notifyListeners(cameraMessage);
    delete cameraMessage;

    EventMouseMessage* mouseMessage = new EventMouseMessage(evMouseMoved);
    sf::Vector2f absolute = mousePos + playerView.getCenter() - playerView.getSize() * 0.5f;
    mouseMessage->pos = b2Vec2(absolute.x, absolute.y);
    mouseMessage->pos *= (1 / 30.f);
    mouseMessage->sfScreenPos = b2Vec2(mousePos.x, mousePos.y);
    mouseMessage->sfRelScreenPos = b2Vec2(mousePos.x / playerView.getSize().x,
                                          mousePos.y / playerView.getSize().y);
    componentList[0].notifyListeners(mouseMessage);
    delete mouseMessage;
}


void CameraSystem::notify(EventMessage * message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage * posMessage = (EventPosMessage*) message;
        playerPos = sf::Vector2f(posMessage->center.x, posMessage->center.y) * 30.f;
        break;
    }

    case evMouseWheelScrolled: {
        EventMouseMessage* mouseMessage = (EventMouseMessage*) message;
        zoom(mouseMessage->scroll);
        break;
    }

    case evWindowResized: {
        EventResizedMessage* resizedMessage = (EventResizedMessage*) message;
        //playerView.setSize(sf::Vector2f(resizedMessage->width, resizedMessage->height));
        playerView.setSize(sf::Vector2f(resizedMessage->size.x, resizedMessage->size.y));
        playerView.zoom(scrollFactor);
        window->setView(playerView);
        break;
    }
    }

    delete message;;
}


CameraSystem::CameraSystem(sf::RenderWindow * window, CameraShakeSystem& cameraShakeSystem)
    : cameraShakeSystem(cameraShakeSystem) {

    this->window = window;

    Settings settings;
    singleton = GameSystem::createComponent(settings);

    cursor.setTexture(Textures::get("Cursors/normal.png"));
    //cursor.setTexture(Textures::get("projectiles/plasma.png"));
    cursor.setOrigin(64, 64);
    //cursor.rotate(90);
    cursor.setScale(0.2, 0.2);
    //cursor.setOrigin(64,64);
    window->setMouseCursorVisible(false);

    playerView.setCenter(sf::Vector2f(350, 300));
    playerView.setSize(sf::Vector2f(initWindowWidth, initWindowHeight));
    playerView.zoom(1.f);
    window->setView(playerView);
}
