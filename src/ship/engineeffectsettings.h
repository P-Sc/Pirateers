/**
 * @file engineeffectsettings.h
 */
#ifndef ENGINEEFFECTSETTINGS_H
#define ENGINEEFFECTSETTINGS_H

#include <Box2D/Common/b2Math.h>
#include "base/settings.h"


struct EngineEffectSettings : Settings {
    b2Vec2 offset; ///< Bestimmt den Versatz von der gesetzten Position
    float size = 4;
};

#endif // ENGINEEFFECTSETTINGS_H
