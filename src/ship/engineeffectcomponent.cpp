#include "engineeffectcomponent.h"

/**
 * @brief Triebwerkseffekt an-/ausschalten
 * @param toggled Schaltet Effekte an, falls True
 */
void EngineEffectComponent::toggleEngine(bool toggled) {
    EventMessage* message = new EventMessage;
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->file =  "engine.wav";

    if (toggled) {
        message->event = cmActivate;
        soundMessage->event  = cmPlaySound;
    } else {
        message->event = cmDeactivate;
        soundMessage->event = cmPauseSound;
    }

    notifyListeners(message);
    notifyListeners(soundMessage);

    delete message;
    delete soundMessage;

    engineToggled = toggled;
}

/**
 * @brief Pausiert Effekte
 */
void EngineEffectComponent::pause() {
    if (engineToggled) {
        EventSoundMessage* soundMessage = new EventSoundMessage;
        soundMessage->file =  "engine.wav";
        soundMessage->event = cmPauseSound;
        notifyListeners(soundMessage);
    }
}

/**
 * @brief Stellt Zustand vor dem Pausieren wieder her
 */
void EngineEffectComponent::resume() {
    if (engineToggled) {
        EventSoundMessage* soundMessage = new EventSoundMessage;
        soundMessage->file =  "engine.wav";
        soundMessage->event  = cmPlaySound;
        notifyListeners(soundMessage);
    }
}

/**
 * @copydoc Component::notify
 * - ::evMove Position aktualisieren
 * - ::cmPowerEngines Effekte an-/ausschalten
 * - ::cmActivate Komponente einschalten
 * - ::cmDeactivate Komponente ausschalten
 */
void EngineEffectComponent::notify(EventMessage* message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        posMessage->pos += b2Mul(b2Rot(posMessage->rotation), settings.offset);
        notifyListeners(posMessage);
        break;
    }

    case cmPowerEngines: {

        if (engineToggled && (message->value < 0.1f && message->value > -0.1f)) {
            toggleEngine(false);
        } else if (settings.active && !engineToggled
                   && (message->value >= 0.1f || message->value <= -0.1f)) {
            toggleEngine(true);
        }

        break;
    }

    case cmActivate: {
        settings.active = true;
        break;
    }

    case cmDeactivate: {
        settings.active = false;
        toggleEngine(false);
        break;
    }
    }

    delete message;;
}

EngineEffectComponent::EngineEffectComponent(EngineEffectSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {

    Event events[6] = {evMove, cmPlaySound, cmPauseSound, cmStopSound, cmActivate, cmDeactivate};
    initializeEvents(events, 6);

}
