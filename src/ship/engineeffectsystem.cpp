#include "engineeffectsystem.h"
#include "graphics/lightsystem.h"
#include "sound/soundsystem.h"


/**
 * @copydoc GameSystem::update
 * Schaltet Effekte bei Bedarf für alle Komponenten ein/aus
 */
void EngineEffectSystem::update(float dt) {
    GameSystem::update(dt);

    if (disableEngines) {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            componentList[i].pause();
        }

        disableEngines = false;
    } else if (resumeEngines) {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            componentList[i].resume();
        }

        resumeEngines = false;
    }
}


/**
 * @copydoc GameSystem::notify
 * - ::evMainMenuOpened Pausiert Effekte
 * - ::evMainMenuClosed Schaltet Effekte wieder ein
 */
void EngineEffectSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evMainMenuOpened: {
        disableEngines = true;
        break;
    }

    case evMainMenuClosed: {
        resumeEngines = true;
        break;
    }
    }

    delete message;
}

Handle* EngineEffectSystem::createComponent(EngineEffectSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);

    LightSettings lightSettings;
    lightSettings.size = settings.size;
    //lightSettings.color = sf::Color(50, 100, 255, 150);
    lightSettings.color = sf::Color(255, 100, 0, 150);
    lightSettings.pos = settings.offset;
    lightSettings.active = false;
    Handle* lightHandle = lightSystem.createComponent(lightSettings);

    SoundSettings soundSettings;
    soundSettings.loop = true;
    soundSettings.volume = 20;
    soundSettings.filename = "engine.wav";
    Handle* soundHandle = soundSystem.createComponent(soundSettings);

    registerComponentAsListener(handle->id, evMove, lightHandle->id, lightSystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, lightHandle->id, lightSystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, lightHandle->id, lightSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, soundHandle->id, soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPauseSound, soundHandle->id, soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmStopSound, soundHandle->id, soundSystem.getEventManager());

    editLock.lock();
    getComponent(handle->id)->lightHandle = lightHandle;
    getComponent(handle->id)->soundHandle = soundHandle;
    editLock.unlock();


    return handle;
}

void EngineEffectSystem::eraseComponent(unsigned int id) {
    if (indices.isUsed(id)) {
        editLock.lock();
        Handle* soundHandle = getComponent(id)->soundHandle;
        Handle* lightHandle = getComponent(id)->lightHandle;
        editLock.unlock();

        delete soundHandle;
        delete lightHandle;

        GameSystem::eraseComponent(id);
    }
}

EngineEffectSystem::EngineEffectSystem(LightSystem& lightSystem, SoundSystem& soundSystem)
    : lightSystem(lightSystem), soundSystem(soundSystem) {

}
