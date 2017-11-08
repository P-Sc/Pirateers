/**
 * @file rewardsettings.h
 */

#ifndef REWARDSETTINGS_H
#define REWARDSETTINGS_H

#include <Box2D/Common/b2Math.h>
#include "base/settings.h"

/**
 * @class RewardSettings
 * @brief Speichert Position und Credit-Anzahl
 */
struct RewardSettings : Settings {
    b2Vec2 pos;
    int credits = 100 + (rand() % 400);
};

#endif // REWARDSETTINGS_H
