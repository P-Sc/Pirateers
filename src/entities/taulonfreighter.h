#ifndef TAULONFREIGHTER_H
#define TAULONFREIGHTER_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class TaulonFreighter : public EnemyShip
{
public:
    TaulonFreighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                    float multiplier = 1.f);
};

#endif // TAULONFREIGHTER_H
