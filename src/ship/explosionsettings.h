/**
 * @file explosionsettings.h
 */
#ifndef EXPLOSIONSETTINGS_H
#define EXPLOSIONSETTINGS_H

#include <Box2D/Common/b2Math.h>
#include "base/settings.h"
#include "sound/soundsettings.h"


/**
 * @struct ExplosionSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit ExplosionComponent und ExplosionSystem benutzt.
 */
struct ExplosionSettings : Settings {
    float size = 10, delay = 0;
    SoundSettings soundSettings;
    b2Vec2 pos;
};


#endif // EXPLOSIONSETTINGS_H
