/**
 * @file soundcomponent.h
 */

#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "SFML/Audio/Sound.hpp"
#include "base/component.h"
#include "handle.h"
#include "sound/soundsettings.h"


/**
 * @class SoundComponent
 * @brief Tonkomponente. Verwaltet Soundeffekte.
 *
 * Wird mit SoundSettings und SoundSystem benutzt.
 */
class SoundComponent : public Component {
private:
    SoundSettings settings;
public:
    float delay = 0;
    bool singlePlayBack = false, hasPlayed = false;
    sf::Sound sound;

    bool tick(float dt);
    virtual void notify(EventMessage *message);
    SoundComponent(SoundSettings settings, Handle* handle);
};

#endif // SOUNDCOMPONENT_H
