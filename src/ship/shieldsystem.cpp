#include "shieldsystem.h"
#include "sound/soundsystem.h"
#include "graphics/lightsystem.h"

/**
 * @copydoc GameSystem::update
 * Aktualisiert Komponenten.h
 */
void ShieldSystem::update(float dt) {
    GameSystem::update(dt);

    for (unsigned int i = 0; i < componentList.size(); i++) {
        componentList[i].tick(dt);
    }
}

void ShieldSystem::notify(EventMessage* message) {
    delete message;;
}

Handle* ShieldSystem::createComponent(ShieldSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    SoundSettings soundSettings;
    soundSettings.volume = 50;
    soundSettings.filename = "shield_hit.wav";
    Handle* shieldHitHandle = soundSystem.createComponent(soundSettings);

    soundSettings.volume = 30;
    soundSettings.filename = "hull_hit.wav";
    Handle* hullHitHandle = soundSystem.createComponent(soundSettings);

    soundSettings.volume = 100;
    soundSettings.filename = "shield_up.ogg";
    Handle* shieldUpHandle = soundSystem.createComponent(soundSettings);

    soundSettings.filename = "shield_down.ogg";
    Handle* shieldDownHandle = soundSystem.createComponent(soundSettings);
    editLock.lock();
    getComponent(handle->id)->setLightSystem(&lightSystem);
    getComponent(handle->id)->shieldHitHandle = shieldHitHandle;
    getComponent(handle->id)->hullHitHandle = hullHitHandle;
    getComponent(handle->id)->shieldUpHandle = shieldUpHandle;
    getComponent(handle->id)->shieldDownHandle = shieldDownHandle;
    editLock.unlock();

    registerComponentAsListener(handle->id, cmPlaySound, shieldHitHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, hullHitHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, shieldUpHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, shieldDownHandle->id,
                                soundSystem.getEventManager());
    return handle;
}

void ShieldSystem::eraseComponent(unsigned int id) {
    if (indices.isUsed(id)) {
        editLock.lock();
        Handle* shieldHitHandle = componentList[indices.get(id)].shieldHitHandle;
        Handle* hullHitHandle = componentList[indices.get(id)].hullHitHandle;
        Handle* shieldUpHandle = componentList[indices.get(id)].shieldUpHandle;
        Handle* shieldDownHandle = componentList[indices.get(id)].shieldDownHandle;
        editLock.unlock();

        delete shieldHitHandle;
        delete hullHitHandle;
        delete shieldUpHandle;
        delete shieldDownHandle;

        GameSystem::eraseComponent(id);
    }

}

ShieldSystem::ShieldSystem(SoundSystem& soundSystem, LightSystem& lightSystem)
    : soundSystem(soundSystem), lightSystem(lightSystem) {

}
