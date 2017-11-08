/**
 * @file ModelSettings
 */

#ifndef MODELSETTINGS_H
#define MODELSETTINGS_H

#include <vector>
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "base/settings.h"


/**
 * @struct ModelSettings
 * @brief Speichert Shapes und Position
 */
struct ModelSettings : public Settings {
    std::vector<b2Shape*> shapes;
    float xPos = 0, yPos = 0;
};

#endif // MODELSETTINGS_H
