#ifndef BANDITFREIGHTER_H
#define BANDITFREIGHTER_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class BanditFreighter : public EnemyShip
{
public:
    BanditFreighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                    float multiplier = 1.f);
};

#endif // BANDITFREIGHTER_H
