/**
 * @file aisettings.h
 */

#ifndef AISETTINGS_H
#define AISETTINGS_H

#include "base/settings.h"

/**
 * @brief Speichert KI-Einstellungen
 */
struct AISettings : Settings {
    /**
     * @enum AIType
     * @brief KI-Typen
     */
    enum AIType {fighter,   ///< Jäger.
                 drone,     ///< Drone
                 freighter, ///< Frachter
                 gunship,   ///< Kanonenboot
                 noAI       ///< Keine KI
                };

    float weaponRange = 0,              ///< Waffen-Reichweite
          sightRange = 0,               ///< Sicht-Radius
          combatRadius = 0,             ///< Für ::circling bei ::Drone, ::flanking bei ::gunship, ::hunting bei ::fighter
          projectileVelocity = 150.f;   ///< Projektil-Geschwindigkeit. Nötig zum Zielen.
    AIType type = noAI;
};

#endif // AISETTINGS_H
