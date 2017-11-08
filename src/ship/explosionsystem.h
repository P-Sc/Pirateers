/**
 * @file explosionsystem.h
 */

#ifndef EXPLOSIONSYSTEM_H
#define EXPLOSIONSYSTEM_H

#include "base/gamesystem.h"
#include "ship/explosioncomponent.h"
#include "ship/explosionsettings.h"

class LightSystem;
class SoundSystem;
class CameraShakeSystem;

/**
 * @class ExplosionSyste
 * @brief System zur Verwaltung von Explosionen (ExplosionComponent).
 *
 * Erstellt und aktualisiert Explosionen. (Einmalige) Explosionen
 * können mit spawnExplosion erstellt werden.
 * Die Explosionen bestehen dabei aus mehreren Lichtern, einem SoundComponent
 * und einem CameraShakeComponent
 */
class ExplosionSystem : public GameSystem<ExplosionComponent, ExplosionSettings>
{
private:
    LightSystem& lightSystem;
    SoundSystem& soundSystem;
    CameraShakeSystem& cameraShakeSystem;

    virtual Handle* createComponent(ExplosionSettings settings);
public:
    void spawnExplosion(ExplosionSettings settings);
    virtual void update(float dt);
    virtual void eraseComponent(unsigned int id);
    ExplosionSystem(LightSystem& lightSystem, SoundSystem& soundSystem,
                    CameraShakeSystem& cameraShakeSystem);
};

#endif // EXPLOSIONSYSTEM_H
