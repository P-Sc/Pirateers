/**
 * @file shieldcomponent.
 */
#ifndef SHIELDCOMPONENT_H
#define SHIELDCOMPONENT_H

#include "base/component.h"
#include "ship/shieldsettings.h"

class LightSystem;


/**
 * @class ShieldComponent
 * @brief Schildkomponente. Verwaltet Schild, Rumpf und Treffereffekte.
 *
 * Wird mit ShieldSettings und ShieldSystem benutzt.
 */
class ShieldComponent : public Component {
private:
    LightSystem* lightSystem;
    ShieldSettings settings;
    sf::Color hullHit1 = sf::Color(55, 0, 0),
              hullHit2 = sf::Color(200, 100, 0),
              hullHit3 = sf::Color(255, 255, 255, 200),
              shieldHit1 = sf::Color(4, 4, 100, 150),
              shieldHit2 = sf::Color(0, 200, 200, 150),
              shieldHit3 = sf::Color(15, 15, 180);
    float shield = 0, hull = 0;
    float regenPause = 0;

    void spawnShieldHit(EventHitMessage* hitMessage);
    void spawnHullHit(EventHitMessage* hitMessage);
    void playSound(std::string filename);
    bool regenShield(float value);
    bool regenHull(float value);
    void applyDamage(int damage);
    void reportChange();
public:
    Handle* shieldHitHandle = nullptr;
    Handle* hullHitHandle = nullptr;
    Handle* shieldUpHandle = nullptr;
    Handle* shieldDownHandle = nullptr;
    void setLightSystem(LightSystem* lightSystem);
    void tick(float dt);
    virtual void notify(EventMessage *message);
    ShieldComponent(ShieldSettings settings, Handle* handle);
};

#endif // SHIELDCOMPONENT_H
