/**
 * @file graphicscomponent.h
 */

#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "base/component.h"
#include "graphics/graphicssettings.h"

/**
 * @class GraphicsComponent
 * @brief Eine Grafikkomponente.
 *
 * Wird mit GraphicsSettings und GraphicsSystem benutzt.
 */
class GraphicsComponent : public Component
{
private:
    float scale = 30;
    bool test = false;
    bool visible = true;
    GraphicsSettings settings;
protected:
public:
    sf::Sprite sprite;
    virtual void notify(EventMessage * message);
    bool isVisible(unsigned int layer = 0);
    bool usesShader();
    void setVisible(bool visible);
    std::string getTextureName();
    GraphicsComponent(GraphicsSettings settings, Handle* handle);
};

#endif // GRAPHICSCOMPONENT_H
