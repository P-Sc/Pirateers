/**
 * @file shipcomponent.h
 */

#ifndef SHIPCOMPONENT_H
#define SHIPCOMPONENT_H

#include "base/component.h"
#include "ship/shipsettings.h"
//#include <set>


/**
 * @class ShipComponent
 * @brief Eine Schiff.
 *
 * Wird mit ShipSettings und ShipSystem benutzt.
 */
class ShipComponent : public Component
{
private:
    bool rotating = false;
    //std::set<Keyboard::Key> pressedKeys;
    //sf::Vector2f relCameraOffset;

    void applyThrust(float percentage);
public:
    ShipSettings settings;
    b2Vec2 pos;
    bool exploding = false;
    float explosionSize = 0, explosionDelayThreshold = 0;
    Handle* physicsHandle = nullptr;
    Handle* graphicsHandle = nullptr;
    Handle* modelHandle = nullptr;
    Handle* tagHandle = nullptr;
    Handle* shieldHandle = nullptr;
    Handle* energyHandle = nullptr;
    Handle* engineEffectHandle = nullptr;
    std::vector<Handle*> weaponHandles;

    virtual void notify(EventMessage* message);
    ShipComponent(ShipSettings settings, Handle* handle);
};

#endif // SHIPCOMPONENT_H
