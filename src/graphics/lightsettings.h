/**
 * @lightsettings.h
 */
#ifndef LIGHTSETTINGS_H
#define LIGHTSETTINGS_H

#include <SFML/Graphics/Color.hpp>
#include <box2d/b2_math.h>
#include "base/settings.h"


/**
 * @struct LightSettings
 * @brief Speicherklasse für Lichter.
 */
struct LightSettings : Settings {
    sf::Color color = sf::Color(255,255,255);
    float size = 10; ///< Größe in m
    b2Vec2 pos; ///< Position in m
};

#endif // LIGHTSETTINGS_H
