#include "explosioncomponent.h"


/**
 * @brief Aktualisiert Komponente. Verwaltet ShakeHandle.
 * @param dt Zeit in ms
 * @return True, falls Explosion vorbei.
 */
bool ExplosionComponent::tick(float dt) {
    if (!triggered) {
        delay -= dt / 1000.f;

        if (delay <= 0) {
            EventMessage* message = new EventMessage(cmShake);
            notifyListeners(message);
            delete message;
            triggered = true;
        }
    } else {
        duration -= dt / 1000.f;

        if (duration <= 0) {
            return true;
        }
    }
    return false;
}

ExplosionComponent::ExplosionComponent(ExplosionSettings settings, Handle* handle)
    : Component(settings, handle) {
    Event events[1] = {cmShake};
    initializeEvents(events, 1);
}
