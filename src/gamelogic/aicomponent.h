/**
 * @file aicomponent.h
 */
#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "base/component.h"
#include "gamelogic/aisettings.h"

/**
 * @enum State
 * @brief Zustände der KI
 */
enum State {hunting,    ///< Jagt den Gegner. Führt "fly-by"-Angriffe aus
            circling,   ///< Umkreist den Gegner
            retreating, ///< Rückzug
            flanking,   ///< Versucht immer in einem Bereich um den Spieler zu bleiben
            idling};    ///< Nichts tun


/**
 * @class AIComponent
 * @brief KI-Komponente. Als Zustandsmaschine implementiert.
 *
 * Benutzt die Zustände aus State für jeden AIType.
 */
class AIComponent : public Component {
private:
    State state = idling;
    AISettings settings;
    b2Vec2 pos, vel, playerPos, playerVel, rot, targetPos;
    bool inCombat = false, isFiring = false, dead = false, superiourAim = false;
    int hull = 0, maxHull = 0, shield = 0, maxShield = 0, energy = 0, maxEnergy = 0;

    float distanceTo(b2Vec2& pos);
    void aim();
    void rotateTo(b2Vec2& pos);
    void stopRotating();
    void powerEngines(float percentage);
    void setFireMode(bool firing);
public:
    sf::Text stateText, aimText;
    sf::CircleShape targetShape;
    sf::Vertex targetLine[2];

    void setState(State newState);
    bool isDead();
    void updateState();
    void update();
    void setPlayerPos(b2Vec2& playerPos, b2Vec2& playerVel);
    void setSuperiourAim(bool superiourAim);
    bool isInCombat();
    virtual void notify(EventMessage *message);
    AIComponent(AISettings settings, Handle* handle);
};

#endif // AICOMPONENT_H
