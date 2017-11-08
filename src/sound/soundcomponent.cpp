#include "soundcomponent.h"


/**
 * @brief Aktualisiert Komponente.
 * @param dt Zeit in ms.
 * @return True, falls Komponente gelöscht werden kann.
 */
bool SoundComponent::tick(float dt) {
    if (!hasPlayed) {
        delay -= dt / 1000.f;

        if (delay <= 0) {
            sound.play();
            hasPlayed = true;
        }
    } else if (hasPlayed && (sound.getStatus() == sf::Sound::Stopped)) {
        return true;
    }
    return false;

}


/**
 * @copydoc Component::notify
 * - ::cmPlaySound Sound abspielen, falls Name übereinstimmt
 * - ::cmPauseSound Sound pausieren, falls Name übereinstimmt
 * - ::cmStopSound Sound stoppen, falls Name übereinstimmt
 */
void SoundComponent::notify(EventMessage* message) {
    switch (message->event) {
    case cmPlaySound: {
        EventSoundMessage* soundMessage = (EventSoundMessage*) message;

        if (soundMessage->file == settings.filename) {
            sound.play();
        }
        break;
    }
    case cmPauseSound: {
        EventSoundMessage* soundMessage = (EventSoundMessage*) message;

        if (soundMessage->file == settings.filename) {
            sound.pause();
        }
        break;
    }
    case cmStopSound: {
        EventSoundMessage* soundMessage = (EventSoundMessage*) message;

        if (soundMessage->file == settings.filename) {
            sound.stop();
        }
        break;
    }
    }

    delete message;;
}

SoundComponent::SoundComponent(SoundSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {

    sound.setVolume(settings.volume);

    if (settings.loop) {
        sound.setLoop(true);
    }

    //Event events[3] = {cmOpenFire, cmCeaseFire, cmRotateTo};
    //initializeEvents(events, 3);

}
