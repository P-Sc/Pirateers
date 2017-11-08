#include "weaponsystem.h"
#include <Box2D/Box2D.h>
#include "physics/physicssystem.h"
#include "graphics/graphicssystem.h"
#include "debug/modelsettings.h"
#include "debug/modeldisplaysystem.h"
#include "ship/ammosystem.h"
#include "ship/weaponloader.h"

void WeaponSystem::update(float dt) {
    GameSystem::update(dt);
}

Handle *WeaponSystem::createComponent(Weapon weapon, Handle* shipPhysicsHandle) {

    WeaponSettings settings;

    if (weapon.gunName == "plasma") {
        settings = WeaponLoader::plasma;
    } else if (weapon.gunName == "neutron") {
        settings = WeaponLoader::neutron;
    } else if (weapon.gunName == "taychon") {
        settings = WeaponLoader::taychon;
    } else {
        settings = WeaponLoader::laser;
    }
    settings.slot = weapon.slot;

    settings.ammoSettings.damage *= weapon.damageMultiplier;
    settings.ammoSettings.rateOfFire *= weapon.rateOfFireMultiplier;
    settings.ammoSettings.velocity *= weapon.velocityMultiplier;
    settings.ammoSettings.scatter *= weapon.scatterMultiplier;
    settings.ammoSettings.notColliding = shipPhysicsHandle;

    if (!weapon.enableShake)
        settings.ammoSettings.cameraShakeSettings.active = false;

    Handle* handle = GameSystem::createComponent(settings);
    Handle* physicsHandle = physicsSystem.createComponent(settings.physicsSettings);
    Handle* graphicsHandle = graphicsSystem.createComponent(settings.graphicsSettings);
    Handle* modelHandle = modelDisplaySystem.createComponent(settings.modelSettings);
    Handle* ammoHandle = ammoSystem.createComponent(settings.ammoSettings);

    editLock.lock();
    componentList[indices.get(handle->id)].physicsHandle = physicsHandle;
    componentList[indices.get(handle->id)].graphicsHandle = graphicsHandle;
    componentList[indices.get(handle->id)].modelHandle = modelHandle;
    componentList[indices.get(handle->id)].ammoHandle = ammoHandle;
    editLock.unlock();

    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            modelHandle->id, modelDisplaySystem.getEventManager());
    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            graphicsHandle->id, graphicsSystem.getEventManager());
    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            ammoHandle->id, ammoSystem.getEventManager());
    registerComponentAsListener(handle->id, cmOpenFire,
                                ammoHandle->id, ammoSystem.getEventManager());
    registerComponentAsListener(handle->id, cmCeaseFire,
                                ammoHandle->id, ammoSystem.getEventManager());
    registerComponentAsListener(handle->id, evEnergyStatus,
                                ammoHandle->id, ammoSystem.getEventManager());
    ammoSystem.registerComponentAsListener(ammoHandle->id, evEnergyUsed,
                                           handle->id, getEventManager());
    registerComponentAsListener(handle->id, cmRotateTo, physicsHandle->id,
                                physicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmUpgrade,
                                ammoHandle->id, ammoSystem.getEventManager());

    registerComponentAsListener(handle->id, cmActivate, physicsHandle->id,
                                physicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, graphicsHandle->id,
                                graphicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, modelHandle->id,
                                modelDisplaySystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, ammoHandle->id,
                                ammoSystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, physicsHandle->id,
                                physicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, graphicsHandle->id,
                                graphicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, modelHandle->id,
                                modelDisplaySystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, ammoHandle->id,
                                ammoSystem.getEventManager());

    editLock.lock();
    b2Body* weaponBody = physicsSystem.getBody(physicsHandle->id);
    b2Body* shipBody = physicsSystem.getBody(shipPhysicsHandle->id);
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = shipBody;
    jointDef.bodyB = weaponBody;
    jointDef.collideConnected = false;
    jointDef.localAnchorA = weapon.entityAnchor;
    jointDef.localAnchorB = settings.weaponAnchor;

    if (weapon.enableLimit) {
        jointDef.lowerAngle = weapon.lowerAngle;
        jointDef.upperAngle = weapon.upperAngle;
    }

    b2RevoluteJoint* joint = (b2RevoluteJoint*) world->CreateJoint(&jointDef);


    editLock.unlock();
    return handle;
}

void WeaponSystem::eraseComponent(unsigned int id) {
    editLock.lock();
    Handle* graphicsHandle = componentList[indices.get(id)].graphicsHandle;
    Handle* physicsHandle = componentList[indices.get(id)].physicsHandle;
    Handle* modelHandle = componentList[indices.get(id)].modelHandle;
    Handle* ammoHandle = componentList[indices.get(id)].ammoHandle;
    editLock.unlock();
    delete graphicsHandle;
    delete physicsHandle;
    delete modelHandle;
    delete ammoHandle;
    GameSystem::eraseComponent(id);
}

WeaponSystem::WeaponSystem(PhysicsSystem& physicsSystem, GraphicsSystem& graphicsSystem,
                           ModelDisplaySystem & modelDisplaySystem, AmmoSystem &ammoSystem)
    : world(physicsSystem.getWorld()), physicsSystem(physicsSystem), graphicsSystem(graphicsSystem)
    , modelDisplaySystem(modelDisplaySystem), ammoSystem(ammoSystem), GameSystem() {

    //WeaponLoader::initializeWeapons();
}
