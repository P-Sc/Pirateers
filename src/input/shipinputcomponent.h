/**
 * @file shipinputcomponent.h
 */
#ifndef SHIPINPUTCOMPONENT_H
#define SHIPINPUTCOMPONENT_H

#include "base/component.h"
#include "input/shipinputsettings.h"

/**
 * @class ShipInputComponent
 * @brief Dummy-Komponente zum versenden von Nachrichten
 */
class ShipInputComponent : public Component
{
public:
    ShipInputComponent(ShipInputSettings settings, Handle* handle);
};

#endif // SHIPINPUTCOMPONENT_H
