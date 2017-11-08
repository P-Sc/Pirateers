/**
 * @file aisystem.h
 */

#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <SFML/Graphics/Font.hpp>
#include "base/gamesystem.h"
#include "gamelogic/aicomponent.h"
#include "gamelogic/aisettings.h"

namespace sf {
    class RenderWindow;
}

/**
 * @class AISystem
 * @brief System zur Verwaltung der künstlichen Intelligenz der Gegner.
 *
 * Aktualisiert alle 500ms die Zustände der Gegner.
 * Malt zudem die Bewegungspfade der Gegner.
 */
class AISystem : public GameSystem<AIComponent, AISettings> {
private:
    b2Vec2 playerPos, playerVel;
    const float STATE_UPDATE_INTERVAL = 500;
    float stateUpdateThreshold = 0;
    bool playerInCombat = false, drawDebug = false, playerSet = true,superiourAim = false,
            aimSettingsChanged = false;
    sf::RenderWindow* window;
    sf::Font debugFont;
public:
    void setSuperiourAim(bool superiourAim);
    void setCombatStatus(bool playerInCombat);
    virtual void update(float dt);
    virtual Handle* createComponent(AISettings settings);
    virtual void notify(EventMessage *message);
    AISystem(sf::RenderWindow* window);
};

#endif // AISYSTEM_H
