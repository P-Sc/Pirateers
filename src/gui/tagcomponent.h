/**
 * @file tagcomponent.h
 */
#ifndef TAGCOMPONENT_H
#define TAGCOMPONENT_H

#include "base/component.h"
#include "gui/tagsettings.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"


/**
 * @class TagComponent
 * @brief Markierungskomponente. Verwaltet HUD für Markierungen von Schiffen.
 *
 * Wird mit ShieldSettings und ShieldSystem benutzt.
 */
class TagComponent : public Component
{
private:
    TagSettings settings;
    int barHeight = 8;
    //int borderWidth = 5;
    float offsetFactor = 0.2f;
public:
    bool visible = true;
    sf::Color hullColor = sf::Color(250, 50, 50),
              hullBackgroundColor = sf::Color(100, 0, 0),
              shieldColor = sf::Color(90, 90, 250),
              shieldBackgroundColor = sf::Color(0, 0, 100),
              energyColor = sf::Color(255, 200, 0),
              energyBackgroundColor = sf::Color(70, 50, 0);
    sf::Sprite arrow;
    sf::ConvexShape borderLeft, borderRight, borderTopLeft, borderTopRight, borderBottomLeft,
                       borderBottomRight;
    sf::RectangleShape hullBar, hullBorderBar, hullBackgroundBar,
                       shieldBar, shieldBorderBar, shieldBackgroundBar,
                       energyBar, energyBorderBar, energyBackgroundBar;
    virtual void notify(EventMessage *message);
    TagComponent(TagSettings settings, Handle* handle);
};

#endif // TAGCOMPONENT_H
