/**
 * @file engineeffectsystem.h
 */
#ifndef ENGINEEFFECTSYSTEM_H
#define ENGINEEFFECTSYSTEM_H

#include "base/gamesystem.h"
#include "ship/engineeffectcomponent.h"
#include "ship/engineeffectsettings.h"

class LightSystem;
class SoundSystem;


/**
 * @class EngineEffectSystem
 * @brief System zur Verwaltung von Triebwerkeffekten (EngineEffectComponent).
 *
 * Erstellt jedes EngineEffectComponent und pausiert diese, falls das Hauptmenü
 * geöffnet wird.
 */
class EngineEffectSystem : public GameSystem<EngineEffectComponent, EngineEffectSettings> {
private:
    LightSystem& lightSystem;
    SoundSystem& soundSystem;

    bool disableEngines = false, resumeEngines = false;
public:
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(EngineEffectSettings settings);
    void eraseComponent(unsigned int id);
    EngineEffectSystem(LightSystem& lightSystem, SoundSystem& soundSystem);
};

#endif // ENGINEEFFECTSYSTEM_H
