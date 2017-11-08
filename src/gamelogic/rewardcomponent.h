/**
 * @file rewardcomponent.h
 */

#ifndef REWARDCOMPONENT_H
#define REWARDCOMPONENT_H

#include "base/component.h"
#include "gamelogic/rewardsettings.h"


/**
 * @class RewardComponent
 * @brief Credit-Komponente zum aufsammeln
 */
class RewardComponent : public Component {
public:
    RewardSettings settings;
    Handle* graphicsHandle = nullptr;
    Handle* lightHandle = nullptr;

    RewardComponent(RewardSettings settings, Handle* handle);
};

#endif // REWARDCOMPONENT_H
