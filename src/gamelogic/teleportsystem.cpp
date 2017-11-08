#include "teleportsystem.h"
#include "sound/soundsystem.h"
#include "graphics/lightsystem.h"

void TeleportSystem::update(float dt) {
    GameSystem::update(dt);

    for (unsigned int i = 0; i < componentList.size(); i++) {
        componentList[i].tick(dt);
    }
}

Handle* TeleportSystem::createComponent(Settings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    SoundSettings soundSettings;
    soundSettings.filename = "teleport.wav";
    soundSettings.volume = 100;
    Handle* soundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_error.wav";
    Handle* errorSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "flash.wav";
    soundSettings.volume = 10;
    Handle* flashSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "transit.ogg";
    soundSettings.volume = 100;
    Handle* transitSoundHandle = soundSystem.createComponent(soundSettings);

    registerComponentAsListener(handle->id, cmPlaySound, soundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, errorSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, flashSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, transitSoundHandle->id,
                                soundSystem.getEventManager());
    registerSystemAsListener(handle->id, cmSpawnLight, lightSystem.getEventManager());

    editLock.lock();
    getComponent(handle->id)->teleportSoundHandle = soundHandle;
    getComponent(handle->id)->errorSoundHandle = errorSoundHandle;
    getComponent(handle->id)->flashSoundHandle = flashSoundHandle;
    getComponent(handle->id)->transitSoundHandle = transitSoundHandle;
    editLock.unlock();
    return handle;
}

void TeleportSystem::eraseComponent(unsigned int id) {
    editLock.lock();
    Handle* soundHandle = getComponent(id)->teleportSoundHandle;
    Handle* errorSoundHandle = getComponent(id)->errorSoundHandle;
    Handle* flashSoundHandle = getComponent(id)->flashSoundHandle;
    Handle* transitSoundHandle = getComponent(id)->transitSoundHandle;
    editLock.unlock();
    delete soundHandle;
    delete errorSoundHandle;
    delete flashSoundHandle;
    delete transitSoundHandle;

    GameSystem::eraseComponent(id);
}

TeleportSystem::TeleportSystem(SoundSystem& soundSystem, LightSystem& lightSystem)
    : soundSystem(soundSystem), lightSystem(lightSystem) {

}
