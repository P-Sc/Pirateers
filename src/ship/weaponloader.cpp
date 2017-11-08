#include "weaponloader.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
//#include "graphics/graphicssettings.h"

WeaponSettings WeaponLoader::plasma = WeaponLoader::loadPlasma();
WeaponSettings WeaponLoader::laser = WeaponLoader::loadLaser();
WeaponSettings WeaponLoader::neutron = WeaponLoader::loadNeutron();
WeaponSettings WeaponLoader::taychon = WeaponLoader::loadTaychon();



/**
 * @brief Initialisiert Plasmawaffe
 */
WeaponSettings WeaponLoader::loadPlasma() {
    WeaponSettings settings;
    b2PolygonShape * shape;

    settings.ammoSettings.damage = 50;
    settings.ammoSettings.range = 160;
    settings.ammoSettings.rateOfFire = 3.6;
    settings.ammoSettings.velocity = 150;
    settings.ammoSettings.scatter = 0.02f;
    settings.ammoSettings.energyConsumption = 15;
    settings.ammoSettings.soundSettings.volume = 5;
    settings.ammoSettings.soundSettings.filename = "plasma2.wav";
    settings.ammoSettings.graphicsSettings.texture = "projectiles/plasma.png";
    settings.ammoSettings.graphicsSettings.rectWidth = 26;
    settings.ammoSettings.graphicsSettings.rectHeight = 34;
    settings.ammoSettings.graphicsSettings.scale = 2;
    settings.ammoSettings.graphicsSettings.useShader = false;
    settings.ammoSettings.lightSettings.color = sf::Color(0,255,0,25);
    //settings.ammoSettings.lightSettings.size = 6;
    settings.ammoSettings.cameraShakeSettings.amplitude = 3;
    settings.ammoSettings.cameraShakeSettings.duration = 0.25f;
    settings.ammoSettings.cameraShakeSettings.frequency = 72;
    settings.graphicsSettings.texture = "weapons/plasma_gun.png";
    settings.graphicsSettings.rectWidth = 14;
    settings.graphicsSettings.rectHeight = 45;
    settings.graphicsSettings.layer = 3;
    settings.weaponAnchor.Set(0, -0.6f);
    shape = new b2PolygonShape();
    shape->SetAsBox(settings.graphicsSettings.rectWidth * settings.graphicsSettings.scale / 30.f,
                    settings.graphicsSettings.rectHeight * settings.graphicsSettings.scale / 30.f);
    settings.physicsSettings.density = 0.01f;
    settings.physicsSettings.shapes.push_back(shape);
    settings.physicsSettings.category = ENTITY_WEAPON;
    //plasma.physicsSettings.collidingWith = 0xFFFF ^ ENTITY_WEAPON;
    settings.physicsSettings.collidingWith = 0x0;
    settings.modelSettings.shapes.push_back(shape);
    return settings;
}

/**
 * @brief Initialisiert Laserwaffe
 */
WeaponSettings WeaponLoader::loadLaser() {
    WeaponSettings settings;
    b2PolygonShape * shape;

    settings.ammoSettings.damage = 30;
    settings.ammoSettings.range = 160;
    settings.ammoSettings.rateOfFire = 4.1;
    settings.ammoSettings.velocity = 150;
    settings.ammoSettings.scatter = 0.01f;
    settings.ammoSettings.energyConsumption = 10;
     settings.ammoSettings.soundSettings.volume = 5;
    settings.ammoSettings.soundSettings.filename = "taychon2.wav";
    settings.ammoSettings.graphicsSettings.texture = "projectiles/laser.png";
    settings.ammoSettings.graphicsSettings.rectWidth = 27;
    settings.ammoSettings.graphicsSettings.rectHeight = 25;
    settings.ammoSettings.graphicsSettings.scale = 2;
    settings.ammoSettings.graphicsSettings.useShader = false;
    settings.ammoSettings.lightSettings.color = sf::Color(0,0,255,50);
    //settings.ammoSettings.lightSettings.size = 15;
    settings.ammoSettings.cameraShakeSettings.amplitude = 2;
    settings.ammoSettings.cameraShakeSettings.duration = 0.2f;
    settings.ammoSettings.cameraShakeSettings.frequency = 80;
    settings.graphicsSettings.texture = "weapons/laser_gun.png";
    settings.graphicsSettings.rectWidth = 13;
    settings.graphicsSettings.rectHeight = 44;
    settings.graphicsSettings.layer = 3;
    //settings.graphicsSettings.useShader = false;
    settings.weaponAnchor.Set(0, -0.6f);
    shape = new b2PolygonShape();
    shape->SetAsBox(settings.graphicsSettings.rectWidth * settings.graphicsSettings.scale / 30.f,
                    settings.graphicsSettings.rectHeight * settings.graphicsSettings.scale / 30.f);
    settings.physicsSettings.density = 0.01f;
    settings.physicsSettings.shapes.push_back(shape);
    settings.physicsSettings.category = ENTITY_WEAPON;
    //plasma.physicsSettings.collidingWith = 0xFFFF ^ ENTITY_WEAPON;
    settings.physicsSettings.collidingWith = 0x0;
    settings.modelSettings.shapes.push_back(shape);
    return settings;
}

/**
 * @brief Initialisiert Neutronwaffe
 */
WeaponSettings WeaponLoader::loadNeutron() {
    WeaponSettings settings;
    b2PolygonShape * shape;

    settings.ammoSettings.damage = 100;
    settings.ammoSettings.range = 120;
    settings.ammoSettings.rateOfFire = 1.5;
    settings.ammoSettings.velocity = 90;
    settings.ammoSettings.scatter = 0.01f;
    settings.ammoSettings.energyConsumption = 20;
    settings.ammoSettings.soundSettings.volume = 10;
    settings.ammoSettings.soundSettings.filename = "plasma1.wav";
    settings.ammoSettings.graphicsSettings.texture = "projectiles/neutron.png";
    settings.ammoSettings.graphicsSettings.rectWidth = 25;
    settings.ammoSettings.graphicsSettings.rectHeight = 26;
    settings.ammoSettings.graphicsSettings.scale = 4;
    settings.ammoSettings.graphicsSettings.useShader = false;
    settings.ammoSettings.lightSettings.color = sf::Color(255,0,0,15);
    settings.ammoSettings.lightSettings.size = 20;
    settings.ammoSettings.cameraShakeSettings.amplitude = 5;
    settings.ammoSettings.cameraShakeSettings.duration = 0.5f;
    settings.ammoSettings.cameraShakeSettings.frequency = 30;
    settings.graphicsSettings.texture = "weapons/neutron_gun.png";
    settings.graphicsSettings.rectWidth = 16;
    settings.graphicsSettings.rectHeight = 40;
    settings.graphicsSettings.layer = 3;
    settings.weaponAnchor.Set(0, -0.6f);
    shape = new b2PolygonShape();
    shape->SetAsBox(settings.graphicsSettings.rectWidth * settings.graphicsSettings.scale / 30.f,
                    settings.graphicsSettings.rectHeight * settings.graphicsSettings.scale / 30.f);
    settings.physicsSettings.density = 0.01f;
    settings.physicsSettings.shapes.push_back(shape);
    settings.physicsSettings.category = ENTITY_WEAPON;
    //plasma.physicsSettings.collidingWith = 0xFFFF ^ ENTITY_WEAPON;
    settings.physicsSettings.collidingWith = 0x0;
    settings.modelSettings.shapes.push_back(shape);
    return settings;
}


/**
 * @brief Initialisiert Taychonwaffe
 */
WeaponSettings WeaponLoader::loadTaychon() {
    WeaponSettings settings;
    b2PolygonShape * shape;

    settings.ammoSettings.damage = 10;
    settings.ammoSettings.range = 130;
    settings.ammoSettings.rateOfFire = 5;
    settings.ammoSettings.velocity = 220;
    settings.ammoSettings.scatter = 0.01f;
    settings.ammoSettings.energyConsumption = 5;
    settings.ammoSettings.soundSettings.volume = 20;
    settings.ammoSettings.soundSettings.filename = "taychon1.wav";
    settings.ammoSettings.graphicsSettings.texture = "projectiles/taychon.png";
    settings.ammoSettings.graphicsSettings.rectWidth = 11;
    settings.ammoSettings.graphicsSettings.rectHeight = 49;
    settings.ammoSettings.graphicsSettings.scale = 3;
    settings.ammoSettings.graphicsSettings.useShader = false;
    settings.ammoSettings.lightSettings.color = sf::Color(180,0,255,45);
    settings.ammoSettings.lightSettings.size = 7;
    settings.ammoSettings.cameraShakeSettings.amplitude = 1;
    settings.ammoSettings.cameraShakeSettings.duration = 0.1f;
    settings.ammoSettings.cameraShakeSettings.frequency = 100;
    settings.graphicsSettings.texture = "weapons/taychon_gun.png";
    settings.graphicsSettings.rectWidth = 4;
    settings.graphicsSettings.rectHeight = 27;
    settings.graphicsSettings.layer = 3;
    settings.weaponAnchor.Set(0, -0.6f);
    shape = new b2PolygonShape();
    shape->SetAsBox(settings.graphicsSettings.rectWidth * settings.graphicsSettings.scale / 30.f,
                    settings.graphicsSettings.rectHeight * settings.graphicsSettings.scale / 30.f);
    settings.physicsSettings.density = 0.01f;
    settings.physicsSettings.shapes.push_back(shape);
    settings.physicsSettings.category = ENTITY_WEAPON;
    //plasma.physicsSettings.collidingWith = 0xFFFF ^ ENTITY_WEAPON;
    settings.physicsSettings.collidingWith = 0x0;
    settings.modelSettings.shapes.push_back(shape);
    return settings;
}
