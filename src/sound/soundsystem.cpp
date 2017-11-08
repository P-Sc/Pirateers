#include "soundsystem.h"


/**
 * @brief Spielt einmaligen Sound ab
 * @param settings Die SoundSettings
 * @param delay Verzögerung, bis Sound gespielt wurd
 */
void SoundSystem::playSound(SoundSettings settings, float delay) {
    Handle* handle = GameSystem::createComponent(settings);
    editLock.lock();
    getComponent(handle->id)->sound.setBuffer(Sounds::get(settings.filename));
    getComponent(handle->id)->singlePlayBack = true;
    getComponent(handle->id)->delay = std::max(delay, 0.f);
    editLock.unlock();
}

/**
 * @copydoc GameSystem::update
 * Löscht Einmal-Sounds
 */
void SoundSystem::update(float dt) {
    GameSystem::update(dt);

    for (unsigned int i = 0; i < componentList.size(); i++) {
        if (componentList[i].singlePlayBack && componentList[i].tick(dt)) {
            eraseComponent(componentList[i].getId());
        }
    }
}

Handle* SoundSystem::createComponent(SoundSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    getComponent(handle->id)->sound.setBuffer(Sounds::get(settings.filename));
    return handle;
}

void SoundSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        break;
    }
    }
    delete message;;
}

void SoundSystem::eraseComponent(unsigned int id) {
    GameSystem::eraseComponent(id);
}

SoundSystem::SoundSystem() {

}
