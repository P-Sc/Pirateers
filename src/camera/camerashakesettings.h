/**
 * @file camerashakesettings.h
 */

#ifndef CAMERASHAKESETTINGS_H
#define CAMERASHAKESETTINGS_H

#include "base/settings.h"


/**
 * @struct CameraShakeSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit CameraShakeComponent und CameraShakeSystem benutzt.
 */
struct CameraShakeSettings : Settings {
    float duration = 0; ///< Dauer in sekunden
    int frequency = 0,  ///< Frequenz in Hz
        amplitude = 0;  ///< Amplitude in Pixeln
};


#endif // CAMERASHAKESETTINGS_H
