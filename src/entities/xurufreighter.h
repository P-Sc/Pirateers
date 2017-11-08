#ifndef XURUFREIGHTER_H
#define XURUFREIGHTER_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"


class XuruFreighter : public EnemyShip {
public:
    XuruFreighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                  float multiplier = 1.f);
};

#endif // XURUFREIGHTER_H
