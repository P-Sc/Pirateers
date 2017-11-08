/**
 * @file stardustsystem.h
 */

#ifndef STARDUSTSYSTEM_H
#define STARDUSTSYSTEM_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include "base/gamesystem.h"

namespace sf {
    class RenderWindow;
}


/**
 * @class StarDustSystem
 * @brief System zur Darstellung von Weltraumstaub.
 *
 * Besitzt ein Array von Arrays von Punkt-Vertices. Jedes dieser Arrays
 * stellt einen "Block" oder "Gebiet" dar, welches so groß wie der Bildschirm ist.
 * Bei jedem update() wird jeder Block gezeichnet (jeder Punkt-Vertex) stellt ein
 * weißes Weltraumpartikel dar.
 * Diese Blöcke sind in einem 9x9-Feld angeordnet und werden verschoben, sobald sich die
 * Kamera aus diesem Feld bewegt (d.h. dass z.b. die unterste Reihe nach oben verschoben wird,
 * falls die Kamera das Feld nach oben hin verlässt).
 */
class StarDustSystem : public GameSystem<Component, Settings> {
private:
    sf::RenderWindow* window;
    sf::VertexArray* particles[3][3];
    sf::View cameraView;
    sf::FloatRect area;
    float density = 0.0005;
    float scale = 1.f;
    bool windowResized = false;

    void moveColumnLeft();
    void moveColumnRight();
    void moveRowUp();
    void moveRowDown();
    void addOffset(int row, int col, sf::Vector2f offset);
    void rearrangeParticles();
    void createParticles();
    void draw();
public:
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    StarDustSystem(sf::RenderWindow* window);
};

#endif // STARDUSTSYSTEM_H
