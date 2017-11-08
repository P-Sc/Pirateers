/**
 * @file weaponsettings.h
 */
#ifndef WEAPONSETTINGS_H
#define WEAPONSETTINGS_H

#include "Box2D/Common/b2Math.h"
#include "base/settings.h"
#include "handle.h"
#include "graphics/graphicssettings.h"
#include "debug/modelsettings.h"
#include "ship/ammosettings.h"
#include "physics/physicssettings.h"


/**
 * @struct WeaponSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit WeaponComponent und WeaponSystem benutzt.
 */
struct WeaponSettings : Settings {
    Handle* physicsHandle;
    b2Vec2 weaponAnchor;
    //b2Vec2 entityAnchor;
    int slot = -1;
    float lowerAngle = 0, upperAngle = 0;
    bool enableLimit = false;

    GraphicsSettings graphicsSettings;
    PhysicsSettings physicsSettings;
    AmmoSettings ammoSettings;
    ModelSettings modelSettings;
};

#endif // WEAPONSETTINGS_H
