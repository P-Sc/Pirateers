/**
 * @file areacomponent.h
 */

#ifndef AREACOMPONENT_H
#define AREACOMPONENT_H

#include "base/component.h"
#include "base/settings.h"

/**
 * @class AreaComponent
 * @brief Dummy-Klasse zum Versenden von Nachrichten
 */
class AreaComponent : public Component
{
public:
    AreaComponent(Settings settings, Handle* handle);
};

#endif // AREACOMPONENT_H
