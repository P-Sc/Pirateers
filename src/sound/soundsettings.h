/**
 * @file soundsettings.h
 */

#ifndef SOUNDSETTINGS_H
#define SOUNDSETTINGS_H

#include <string>
#include "base/settings.h"


/**
 * @struct SoundSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit SoundComponent und SoundSystem benutzt.
 */
struct SoundSettings : Settings {
    std::string filename;
    float volume = 80;
    bool loop = false;
};


#endif // SOUNDSETTINGS_H
