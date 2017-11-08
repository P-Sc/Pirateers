/**
 * @file graphicssettings.h
 */

#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include "base/settings.h"


/**
 * @struct GraphicsSettings
 * @brief Speicherklasse für Informationen der Komponente.
 *
 * Wird mit GraphicsComponent und GraphicsSystem benutzt.
 */
struct GraphicsSettings : Settings {
    /** @brief Pfad der Textur/ des Sprites
     *
     * Pfad muss relativ zum "resources/textures/"-Ordner sein
     */
    std::string texture = "../resources/purplebrick2.png";
    sf::Vector2f pos;
    sf::Color color = sf::Color::White;
    float scale = 1, rotation = 0;
    int rectX = 0, rectY = 0, rectWidth = 0, rectHeight = 0;
    unsigned int layer = 1;
    bool useShader = true;
};

#endif // GRAPHICSSETTINGS_H
