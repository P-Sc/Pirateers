#ifndef ALIENFIGHTER_H
#define ALIENFIGHTER_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class AlienFighter : public EnemyShip
{
public:
    AlienFighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                 float multiplier = 1.f);
};

#endif // ALIENFIGHTER_H
