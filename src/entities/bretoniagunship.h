#ifndef ORANGEGUNSHIP_H
#define ORANGEGUNSHIP_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class BretoniaGunship : public EnemyShip
{
public:
    BretoniaGunship(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                    float multiplier = 1.f);
};

#endif // ORANGEGUNSHIP_H
