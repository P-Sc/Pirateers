/**
 * @file soundsystem.h
 */

#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "base/gamesystem.h"
#include "sound/soundcomponent.h"
#include "sound/soundsettings.h"
#include "sound/sounds.h"


/**
 * @class SoundSystem
 * @brief System zur Verwaltung von Sounds
 *
 * Erstellt und aktualisert Sounds. Kann Einmal-Sounds abspielen.
 */
class SoundSystem : public GameSystem<SoundComponent, SoundSettings> {
private:
    b2Vec2 cameraCenter;
    float scrollingFactor;
public:
    void playSound(SoundSettings settings, float delay);
    virtual void update(float dt);
    virtual Handle* createComponent(SoundSettings settings);
    virtual void notify(EventMessage *message);
    virtual void eraseComponent(unsigned int id);
    SoundSystem();
};

#endif // SOUNDSYSTEM_H
