/**
 * @file inputsystem.h
 */

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "base/gamesystem.h"
#include "input/inputcomponent.h"

namespace sf {
    class RenderWindow;
}

/**
 * @class InputSystem
 * @brief GameSystem für die Spielereingaben.
 *
 * Wird mit InputComponent und Settings benutzt.
 */
class InputSystem : public GameSystem<InputComponent,Settings>
{
private:
    Handle* singleton;
    sf::RenderWindow* window;
    int windowWidth, windowHeight;
    void enterMouseCoordinates(EventMouseMessage* message, int x, int y);
    virtual Handle* createComponent(Settings settings);
public:
    virtual void update(float dt);
    InputSystem(sf::RenderWindow * window);
};

#endif // INPUTSYSTEM_H
