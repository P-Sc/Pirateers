/**
 * @file shieldsystem.h
 */
#ifndef SHIELDSYSTEM_H
#define SHIELDSYSTEM_H

#include "base/gamesystem.h"
#include "ship/shieldcomponent.h"

class LightSystem;
class SoundSystem;

/**
 * @class ShieldSystem
 * @brief System zur Verwaltung von Schild- und Rumpfpunkten.
 *
 * Erstellt und aktualisiert jedes ShieldComponent.
 */
class ShieldSystem : public GameSystem<ShieldComponent, ShieldSettings> {
private:
    SoundSystem& soundSystem;
    LightSystem& lightSystem;
    sf::Color hullHit1 = sf::Color(55, 0, 0),
              hullHit2 = sf::Color(200, 100, 0),
              hullHit3 = sf::Color(255, 255, 255),
              shieldHit1 = sf::Color(0, 0, 55),
              shieldHit2 = sf::Color(0, 0, 100),
              shieldHit3 = sf::Color(15, 15, 180);
public:
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(ShieldSettings settings);
    virtual void eraseComponent(unsigned int id);
    ShieldSystem(SoundSystem& soundSystem, LightSystem& lightSystem);
};

#endif // SHIELDSYSTEM_H
