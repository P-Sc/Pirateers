#include "explosionsystem.h"
#include "graphics/lightsystem.h"
#include "sound/soundsystem.h"
#include "camera/camerashakesystem.h"

Handle* ExplosionSystem::createComponent(ExplosionSettings settings) {
    return GameSystem::createComponent(settings);
}

/**
 * @brief Explosion erstellen
 * @param settings Einstellungen für Explosion
 */
void ExplosionSystem::spawnExplosion(ExplosionSettings settings) {
    float duration = settings.size / 50.f;
    Handle* handle = createComponent(settings);
    CameraShakeSettings shakeSettings;
    shakeSettings.amplitude = 15;
    shakeSettings.frequency = 200;
    shakeSettings.duration = duration / 3.f;
    Handle* shakeHandle = cameraShakeSystem.createComponent(shakeSettings);
    registerComponentAsListener(handle->id, cmShake, shakeHandle->id,
                                cameraShakeSystem.getEventManager());

    //Handle* soundHandle = soundSystem.createComponent(settings.soundSettings);
    soundSystem.playSound(settings.soundSettings, settings.delay);

    editLock.lock();
    //getComponent(handle->id)->soundHandle = soundHandle;
    getComponent(handle->id)->duration = duration;
    getComponent(handle->id)->delay = settings.delay;
    getComponent(handle->id)->shakeHandle = shakeHandle;
    editLock.unlock();

    if (settings.size > 50) {
        EventLightMessage* flash = new EventLightMessage;
        flash->color = sf::Color(150, 150, 150);
        flash->delay = settings.delay;
        flash->duration = 0.1;
        flash->fadeDelay = 0.1 - 0.1 * 0.7f;
        flash->pos = settings.pos;
        flash->size = 250;
        lightSystem.notify(flash);
    }


    EventLightMessage* light = new EventLightMessage;
    light->color = sf::Color(55, 0, 0);
    light->delay = settings.delay;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos = settings.pos;
    light->size = settings.size;
    lightSystem.notify(light);

    light = new EventLightMessage;
    light->color = sf::Color(200, 100, 0);
    light->delay = settings.delay;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos = settings.pos;
    light->size = settings.size * 2 / 3.f;
    lightSystem.notify(light);

    light = new EventLightMessage;
    light->color = sf::Color(255, 255, 255);
    light->delay = settings.delay;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos = settings.pos;
    light->size = settings.size * 1 / 3.f;
    lightSystem.notify(light);

}

/**
 * @copydoc GameSystem::update
 * Explosionen aktualisieren und ggf. wieder löschen
 */
void ExplosionSystem::update(float dt) {
    GameSystem::update(dt);

    for (unsigned int i = 0; i < componentList.size(); i++) {
        if (componentList[i].tick(dt)) {
            eraseComponent(componentList[i].getId());
        }
    }
}

void ExplosionSystem::eraseComponent(unsigned int id) {
    if (indices.isUsed(id)) {
        editLock.lock();
        Handle* shakeHandle = getComponent(id)->shakeHandle;
        editLock.unlock();

        delete shakeHandle;

        GameSystem::eraseComponent(id);
    }
}

ExplosionSystem::ExplosionSystem(LightSystem& lightSystem, SoundSystem& soundSystem,
                                 CameraShakeSystem& cameraShakeSystem)
    : lightSystem(lightSystem), soundSystem(soundSystem), cameraShakeSystem(cameraShakeSystem) {
}
