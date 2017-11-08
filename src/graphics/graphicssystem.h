/**
 * @file graphicssystem.h
 */

#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <SFML/Graphics/Shader.hpp>
#include "base/gamesystem.h"
#include "graphics/graphicscomponent.h"
#include "graphics/graphicssettings.h"



/**
 * @class GraphicsSystem
 * @brief Das System zur Verwaltung von Grafikelementen.
 *
 * Wird mit GraphicsSettings und GraphicsComponent benutzt.
 * Benutzt SFML.
 */
class GraphicsSystem : public GameSystem<GraphicsComponent, GraphicsSettings>
{
private:
    sf::RenderWindow * window;
    sf::Shader lightShader;
    sf::RenderTexture& lightMap;
    char c[14];
    int frameCount = 0;
    int fps = 0;
    float timeElapsed = 0;
    float blurFactor = 5.f;
    float scrollFactor = 1.f;
    unsigned int LAYER_COUNT = 4;
    void displayFPS(float dt);
public:
    virtual void update(float dt);
    virtual void notify(EventMessage* message);
    virtual Handle* createComponent(GraphicsSettings settings);
    bool isOpen();
    void setPlayerId(unsigned int id);
    GraphicsSystem(sf::RenderWindow* window, sf::RenderTexture& lightMap);
};

#endif // GRAPHICSSYSTEM_H
