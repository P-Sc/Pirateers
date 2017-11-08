/**
 * @file backgroundsystem.h
 */
#ifndef BACKGROUNDSYSTEM_H
#define BACKGROUNDSYSTEM_H

#include "base/gamesystem.h"
#include "graphics/backgroundcomponent.h"
#include "graphics/backgroundsettings.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Clock.hpp>

namespace sf {
    class RenderWindow;
}


/**
 * @class BackgroundSystem
 * @brief System zur Verwaltung von Hintergründen.
 *
 * Lädt Hintergründe und zentriert sie mit der Kamera.
 * Wechselt die Hintergründe bei ::evAreaChange. Setzt verschiedene
 * Einstellungen für jeden Hintergrund, damit Lichteffekte noch gut aussehen.
 */
class BackgroundSystem : public GameSystem<BackgroundComponent, BackgroundSettings> {
private:
    sf::RenderWindow * window;
    sf::Sprite background, startBackground, shopBackground, alienBackground, banditBackground,
               bretoniaBackground, taulanBackground, xuruBackground;
    sf::RenderTexture& lightMap;
    sf::Shader lightShader;
    sf::View cameraView;
    float blurFactor = 5.f;
    float scrollFactor = 1.f;
    bool needsResize = false;
    Area area = Area::StartArea;

    void setBackground();
    void resize();
    void zoom(float scroll);
public:
    virtual void update(float dt);
    virtual void notify(EventMessage* message);
    BackgroundSystem(sf::RenderWindow * window, sf::RenderTexture& lightMap);
};

#endif // BACKGROUNDSYSTEM_H
