/**
 * @file camerashakecomponent.h
 */

#ifndef CAMERASHAKECOMPONENT_H
#define CAMERASHAKECOMPONENT_H

#include <vector>
#include "base/component.h"
#include "camera/camerashakesettings.h"


/**
 * @brief Komponente für Kamerawackeln
 *
 * Besitzt Dauer, Frequenz und Amplitude. Erstellt ein Array von Samples nach Frequenz und
 * Dauer. Wackeln wird mit linearer Interpolation anhand der Samples bestimmt.
 */
class CameraShakeComponent : public Component {
private:
    CameraShakeSettings settings;
    std::vector<float> xSamples, ySamples;
    float remainingDuration = 0.f, time = 0.f;
    int indexOffset = 0;
    float getDecay(float time);
    sf::Vector2f getSample(int index);
public:
    void trigger();
    void tick(float dt);
    bool isShaking();
    sf::Vector2f getOffset();
    virtual void notify(EventMessage *message);
    CameraShakeComponent(CameraShakeSettings settings, Handle* handle);
};

#endif // CAMERASHAKECOMPONENT_H
