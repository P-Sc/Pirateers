/**
 * shopsettings.h
 */

#ifndef SHOPSETTINGS_H
#define SHOPSETTINGS_H

#include <box2d/b2_math.h>
#include "base/settings.h"

/**
 * @brief Enthält Position
 */
struct ShopSettings : Settings {
    b2Vec2 pos;
};

#endif // SHOPSETTINGS_H
