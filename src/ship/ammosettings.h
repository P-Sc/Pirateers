/**
 * @file ammosettings.h
 */
#ifndef AMMOSETTINGS_H
#define AMMOSETTINGS_H

#include <vector>
#include "handle.h"
#include "base/settings.h"
#include "graphics/graphicssettings.h"
#include "graphics/lightsettings.h"
#include "camera/camerashakesettings.h"
#include "sound/soundsettings.h"

class GraphicsSystem;
class PhysicsSystem;

/**
 * @struct AmmoSettings
 * @brief Speicherklasse für AmmoComponent. Enthält Einstellungen zum Feuern und den Projektilen
 *
 * Wird mit AmmoComponent und AmmoSystem benutzt.
 */
struct AmmoSettings : Settings {
public:
    float damage = 0, range = 0, velocity = 0, rateOfFire = 0, scatter = 1, energyConsumption = 0;
    GraphicsSettings graphicsSettings;
    LightSettings lightSettings;
    CameraShakeSettings cameraShakeSettings;
    SoundSettings soundSettings;
    Handle* notColliding;
};


#endif // AMMOSETTINGS_H
