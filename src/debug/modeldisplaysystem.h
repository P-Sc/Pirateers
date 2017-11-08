/**
 * @file modeldisplaysystem.h
 */

#ifndef MODELDISPLAYSYSTEM_H
#define MODELDISPLAYSYSTEM_H

#include "base/gamesystem.h"
#include "modelcomponent.h"
#include "modelsettings.h"

namespace sf {
    class RenderWindow;
}

/**
 * @class ModelDisplaySystem
 * @brief Zeichnet b2Shapes
 *
 * Wird mit ModelComponent und ModelSettings benutzt und kann dazu verwendet
 * werden, Kollisionsmodelle von Box2D zu zeichnen.
 * Benutzt SFML
 */
class ModelDisplaySystem : public GameSystem<ModelComponent, ModelSettings>
{
private:
    sf::RenderWindow * window;
    bool display = false;   ///< Gibt an, ob gezeichnet werden soll
public:
    void setDisplay(bool value);
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(ModelSettings settings);
    ModelDisplaySystem(sf::RenderWindow* window);
};

#endif // MODELDISPLAYSYSTEM_H
