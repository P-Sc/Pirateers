/**
 * @file lightcomponent.h
 */

#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "base/component.h"
#include "graphics/lightsettings.h"

/**
 * @class LightComponent
 * @brief Lichtkomponente. Macht Licht.
 *
 * Wird mit LightSettings und LightSystem benutzt.
 */
class LightComponent : public Component
{
public:
    LightSettings settings;
    sf::Sprite light;
    float resolutionFactor = 0.2f, ///< Verkleinerungsfaktor des Lichtsystems
          duration = -1,           ///< Dauer
          delay = 0,               ///< Verzögerung zum Aufleuchten
          fadeDelay = 0,           ///< Verzögerung zum Anfang des Ausblendens
          fadeDuration = 0;        ///< Ausblendedauer
    //sf::VertexArray vertices;

    LightSettings& getSettings();
    bool tick(float dt);
    virtual void notify(EventMessage *message);
    LightComponent(LightSettings settings, Handle* handle);
};

#endif // LIGHTCOMPONENT_H
