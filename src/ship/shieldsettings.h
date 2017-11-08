/**
 * @file shieldsettings.h
 */
#ifndef SHIELDSETTINGS_H
#define SHIELDSETTINGS_H

#include "base/settings.h"


/**
 * @struct ShieldSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit ShieldComponent und ShieldSystem benutzt.
 */
struct ShieldSettings : Settings {
    int maxHull = 0, maxShield = 0;
    float regenPerSecond = 0, maxRegenPause = 0;
};

#endif // SHIELDSETTINGS_H
