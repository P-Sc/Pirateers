#include "camerashakecomponent.h"

/**
 * @brief Verfall nach der Zeit berechnen
 * @param time Die vergangene Zeit in Sekunden
 * @return Der Verfall als Faktor
 */
float CameraShakeComponent::getDecay(float time) {
    if (time > settings.duration) {
        return 0;
    } else {
        return (settings.duration - time) / settings.duration;
    }
}


/**
 * @brief Gibt ein Sample zurück
 * @param index Der index des Samples
 * @return Das Sample
 */
sf::Vector2f CameraShakeComponent::getSample(int index) {
    int i = (index + indexOffset) % xSamples.size();
    sf::Vector2f sample;
    sample.x = xSamples[i];
    sample.y = ySamples[i];

    return sample;

}

/**
 * @brief Löst das Wackeln aus
 */
void CameraShakeComponent::trigger() {
    if (remainingDuration > 0) {
        indexOffset = floor(time * settings.frequency) + indexOffset + 1;
    }

    remainingDuration = settings.duration;
}


/**
 * @brief Aktualisiert die vergangene Zeit
 * @param dt Zeit in ms
 */
void CameraShakeComponent::tick(float dt) {
    if (remainingDuration - dt / 1000.f > 0) {
        remainingDuration -= dt / 1000.f;
    } else {
        remainingDuration = 0;
    }
}


/**
 * @brief Gibt an, ob Komponente aktiv
 * @return True, falls noch am wackeln
 */
bool CameraShakeComponent::isShaking() {
    return (remainingDuration > 0) && settings.active;
}

/**
 * @brief Gibt die Verschiebung zurück
 * @return Die Verschiebung
 */
sf::Vector2f CameraShakeComponent::getOffset() {
    time = settings.duration - remainingDuration;
    float s = time * settings.frequency;
    int s0 = floor(s);
    int s1 = s0 + 1;

    return (getSample(s0) + (s - s0) * (getSample(s1) - getSample(s0))) * getDecay(time)
           * (float) settings.amplitude;

}

/**
 * @copydoc GameSystemComponent::notify
 * - ::cmShake Löst das Kamerabeben aus
 */
void CameraShakeComponent::notify(EventMessage* message) {
    switch (message->event) {
    case cmShake: {
        trigger();
        break;
    }
    }

    delete message;;
}

CameraShakeComponent::CameraShakeComponent(CameraShakeSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {

    int sampleCount = (settings.duration) * settings.frequency;
    if (sampleCount == 0)
        sampleCount = 1;
    //float samples[sampleCount];
    xSamples.resize(sampleCount);
    ySamples.resize(sampleCount);

    for (int i = 0; i < sampleCount; i++) {
        xSamples[i] = (rand() % 200000 - 100000) / 100000.f;
        ySamples[i] = (rand() % 200000 - 100000) / 100000.f;
    }
}
