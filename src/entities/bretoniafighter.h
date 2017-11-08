#ifndef ORANGEFIGHTER_H
#define ORANGEFIGHTER_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class BretoniaFighter : public EnemyShip
{
public:
    BretoniaFighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                  float multiplier = 1.f);
};

#endif // ORANGEFIGHTER_H
