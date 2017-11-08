/**
 * @file tagsystem.h
 */
#ifndef TAGSYSTEM_H
#define TAGSYSTEM_H

#include "base/gamesystem.h"
#include "gui/tagcomponent.h"
#include "gui/tagsettings.h"

namespace sf {
    class RenderWindow;
    class Texture;
}

/**
 * @class TagSystem
 * @brief Klasse zur Verwaltung von Schiffs-"Tags" (TagComponent),
 *        also Markierungen mit Statusanzeige für Schiffe.
 *
 * Angezeigt werden Markierung (Rote Balken), Schild-, Rumpf- und Energieinformationen
 * und ein Pfeil am Bildschirmrand, falls sich das Ziel außerhalb der Kamera befindet.
 */
class TagSystem : public GameSystem<TagComponent, TagSettings> {
private:
    sf::RenderWindow* window;
    //sf::Texture& barTexture;
    sf::Texture& arrowTexture;
    sf::Rect<float> cameraBounds;
    sf::Vector2f cameraCenter;
    float scale = 1;
    float arrowScale = 0.6f;

    float getArrowAngle(sf::Vector2f shipPos);
    sf::Vector2f getArrowPos(sf::Vector2f shipPos, float borderOffset);
public:
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(TagSettings settings);
    TagSystem(sf::RenderWindow* window);
};

#endif // TAGSYSTEM_H
