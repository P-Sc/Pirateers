/**
 * @file teleportsystem.h
 */
#ifndef TELEPORTSYSTEM_H
#define TELEPORTSYSTEM_H

#include "base/gamesystem.h"
#include "gamelogic/teleportcomponent.h"
#include "base/settings.h"

class SoundSystem;
class LightSystem;


/**
 * @class TeleportSystem
 * @brief System zur Verwaltung von TeleportComponent
 *
 * Erstellt und aktualisiert lediglich jedes TeleportComponent
 */
class TeleportSystem : public GameSystem<TeleportComponent, Settings> {
private:
    SoundSystem& soundSystem;
    LightSystem& lightSystem;
public:
    virtual void update(float dt);
    virtual Handle* createComponent(Settings settings);
    virtual void eraseComponent(unsigned int id);
    TeleportSystem(SoundSystem& soundSystem, LightSystem& lightSystem);
};

#endif // TELEPORTSYSTEM_H
