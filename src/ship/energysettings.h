/**
 * @file energysettings.h
 */
#ifndef ENERGYSETTINGS_H
#define ENERGYSETTINGS_H

#include "base/settings.h"

/**
 * @struct EnergySettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit EnergyComponent und EnergySystem benutzt.
 */
struct EnergySettings : Settings {
    int maxEnergy = 0;
    float regenPerSecond = 0;
};

#endif // ENERGYSETTINGS_H
