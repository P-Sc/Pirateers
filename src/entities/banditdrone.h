#ifndef BANDITDRONE_H
#define BANDITDRONE_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class BanditDrone : public EnemyShip
{
public:
    BanditDrone(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                float multiplier = 1.f);
};

#endif // BANDITDRONE_H
