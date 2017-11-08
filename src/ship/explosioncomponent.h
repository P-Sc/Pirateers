/**
 * @file explosioncomponent.h
 */
#ifndef EXPLOSIONCOMPONENT_H
#define EXPLOSIONCOMPONENT_H

#include "base/component.h"
#include "ship/explosionsettings.h"


/**
 * @class ExplosionComponent
 * @brief Explosionskomponente. Verwaltet eine einzelne Explosion.
 *
 * Wird mit ExplosionSettings und ExplosionSystem benutzt.
 */
class ExplosionComponent : public Component {
private:
    bool triggered = false;
public:
    bool tick(float dt);
    float delay = 0, duration = 0;
    Handle* shakeHandle = nullptr;
    ExplosionComponent(ExplosionSettings settings, Handle* handle);
};

#endif // EXPLOSIONCOMPONENT_H
