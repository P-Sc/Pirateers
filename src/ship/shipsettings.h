/**
 * @file shipsettings.h
 */

#ifndef SHIPSETTINGS_H
#define SHIPSETTINGS_H

#include <string>
#include <vector>
#include <box2d/b2_math.h>
#include "base/settings.h"
#include "ship/weapon.h"
#include "ship/shieldsettings.h"
#include "ship/energysettings.h"
#include "ship/engineeffectsettings.h"

/**
 * @struct ShipSettings
 * @brief Speicherklassen für Informationen der Komponente
 *
 * Wird mit ShipComponent und ShipSystem benutzt.
 */
struct ShipSettings : Settings {
    std::string shipname = "";
    std::vector<Weapon> weapons;
    ShieldSettings shieldSettings;
    EnergySettings energySettings;
    EngineEffectSettings engineEffectSettings;
    b2Vec2 pos;
    float rotation = 0, explosionDelay = 3.f;
    bool playerControlled;
    int rewardCount = 0;

    /*
     * Unwichtig, falls Schiffname gesetzt
     */
    float propulsion = 0;
    float maxTorque = 0;
};

#endif // SHIPSETTINGS_H
