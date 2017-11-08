#ifndef XURUGUNSHIP_H
#define XURUGUNSHIP_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class XuruGunship : public EnemyShip
{
public:
    XuruGunship(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                float multiplier = 1.f);
};

#endif // XURUGUNSHIP_H
