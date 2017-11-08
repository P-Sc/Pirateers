/**
 * @file tagsettings.h
 */

#ifndef TAGSETTINGS_H
#define TAGSETTINGS_H

#include "base/settings.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

/**
 * @struct TagSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit TagComponent und TagSystem benutzt.
 */
struct TagSettings : Settings {
    sf::Color color;
    float height, gap;
};

#endif // TAGSETTINGS_H
