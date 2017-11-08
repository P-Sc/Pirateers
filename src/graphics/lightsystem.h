/**
 * @lightsystem.h
 */
#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "base/gamesystem.h"
#include "graphics/lightcomponent.h"
#include "graphics/lightsettings.h"


/**
 * @class LightSystem
 * @brief System zur Verwaltung von Lichtern
 *
 * Lichter werden als Sprites mit verschiedener Größe, Farbe, Position, etc. gespeichert
 * (Aber mit der gleichen Textur). Diese werden dann bei jedem Update auf eine
 * sf::RenderTexture gezeichnet, welche dann wiederrum benutzt werden kann, um
 * mit einem Shader andere Sprites zu malen. Siehe dazu BackgroundSystem und
 * GraphicsSystem.
 * Kann zusätzlich noch temporäre Lichter zur einmaligen Verwendung erstellen, um z.B.
 * Explosionen einfacher zu gestalten.
 */
class LightSystem : public GameSystem<LightComponent, LightSettings> {
private:
    sf::RenderTexture lightMap;
    sf::Sprite light;
    sf::View cameraView;
    sf::RenderWindow* window;
    b2Vec2 windowSize;
    float resolutionFactor = 0.2f;
    std::vector<EventLightMessage*> creationQueue;
    void processCreationQueue();
    void createTemporaryComponent(LightSettings settings, float duration, float delay,
                                  float fadeDelay);
public:
    sf::RenderTexture& getLightMap();
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(LightSettings settings);
    LightSystem(sf::RenderWindow* window);
};

#endif // LIGHTSYSTEM_H
