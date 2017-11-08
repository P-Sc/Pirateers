/**
 * @file camerasystem.h
 */

#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "base/gamesystem.h"
#include "camera/cameracomponent.h"

namespace sf {
    class RenderWindow;
}

class CameraShakeSystem;


/**
 * @class CameraSystem
 * @brief System zur Verwaltung der Kamera
 *
 * Stellt die Kameraposition basierend auf der Spielerposition, Mausposition
 * und Shake-Effekten ein. Interpoliert linear die Position der Kamera.
 */
class CameraSystem : public GameSystem<CameraComponent, Settings>
{
private:
    Handle* singleton;
    CameraShakeSystem& cameraShakeSystem;
    sf::RenderWindow * window;
    sf::Sprite background;
    sf::Sprite cursor;
    sf::Vector2f playerPos;
    sf::Vector2f interpolatedCenter;
    sf::Vector2f mousePos;
    sf::View playerView;
    float scrollFactor = 1.f;
    float linearInterpolationFactor = 0.05f;
    float mouseFollowingFactor = 0.1f; // 0.6
    void zoom(float scroll);
public:
    void drawCursor();
    virtual Handle* createComponent(Settings settings);
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    CameraSystem(sf::RenderWindow* window, CameraShakeSystem& cameraShakeSystem);
};

#endif // CAMERASYSTEM_H
