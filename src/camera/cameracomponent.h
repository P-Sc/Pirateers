/**
 * @file camaeracomponent.h
 */

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "base/component.h"
#include "base/settings.h"


/**
 * @class CameraComponent
 * @brief Dummy-Klasse für CameraSystem. Dient nur dem verschicken von Nachrichten
 */
class CameraComponent : public Component
{
public:
    CameraComponent(Settings settings, Handle* handle);
};

#endif // CAMERACOMPONENT_H
