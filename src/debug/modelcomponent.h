/**
 * @file modelcomponent.h
 */

#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Audio.hpp>
#include "base/component.h"
#include "modelsettings.h"



class b2ChainShape;

/**
 * @class ModelComponent
 * @brief Komponente zum Zeichnen von b2Shapes
 *
 * Nimmt jeden Typ von b2Shape und erstellt damit SFML-Shapes.
 */
class ModelComponent : public Component
{
private:
    sf::Color fillColor = sf::Color(0, 250, 0, 150);

    float vecToRad(b2Vec2 v);
    float b2AngleToSfAngle(float rad);

    void addShape(b2PolygonShape* shape);
    void addShape(b2CircleShape* shape);
    void addShape(b2EdgeShape* shape);
    void addShape(b2ChainShape* shape);
public:
    bool visible = true;
    std::vector<sf::CircleShape> circles;
    std::vector<sf::ConvexShape> polygons;
    std::vector<sf::RectangleShape> lines;

    std::vector<sf::Vector2f> circleOffsets;
    std::vector<sf::Vector2f> polygonOffsets;
    std::vector<sf::Vector2f> lineOffsets;
    std::vector<float> lineRotationOffsets;

    virtual void notify(EventMessage *message);
    ModelComponent(ModelSettings settings, Handle* handle);
};

#endif // MODELCOMPONENT_H
