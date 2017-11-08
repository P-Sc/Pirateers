/**
 * @file weaponloader.h
 */

#ifndef WEAPONLOADER_H
#define WEAPONLOADER_H

#include "ship/weaponsettings.h"


/**
 * @class WeaponLoader
 * @brief Lädt Basiswaffentypen.
 */
class WeaponLoader {
private:
    static WeaponSettings loadPlasma();
    static WeaponSettings loadLaser();
    static WeaponSettings loadNeutron();
    static WeaponSettings loadTaychon();
public:
    static WeaponSettings plasma;
    static WeaponSettings laser;
    static WeaponSettings neutron;
    static WeaponSettings taychon;
};

#endif // WEAPONLOADER_H
