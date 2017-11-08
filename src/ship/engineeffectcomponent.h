/**
 * @file engineeffectcomponent.hs
 */
#ifndef ENGINEEFFECTCOMPONENT_H
#define ENGINEEFFECTCOMPONENT_H

#include "base/component.h"
#include "ship/engineeffectsettings.h"


class EngineEffectComponent : public Component {
private:
    EngineEffectSettings settings;
    bool engineToggled = false;

    void toggleEngine(bool toggled);
public:
    Handle* soundHandle = nullptr;
    Handle* lightHandle = nullptr;

    void pause();
    void resume();
    virtual void notify(EventMessage *message);
    EngineEffectComponent(EngineEffectSettings settings, Handle* handle);
};

#endif // ENGINEEFFECTCOMPONENT_H
