#include "shipinputsystem.h"
#include "input/inputsystem.h"
#include "camera/camerasystem.h"

/**
 * @brief Bei nötigen GameSystms anmelden
 */
void ShipInputSystem::registerAsListener() {
    inputSystem.registerSystemAsListener(0, evKeyPressed, getEventManager());
    inputSystem.registerSystemAsListener(0, evKeyReleased, getEventManager());
    cameraSystem.registerSystemAsListener(0, evMouseMoved, getEventManager());
    inputSystem.registerSystemAsListener(0, evMouseButtonPressed, getEventManager());
    inputSystem.registerSystemAsListener(0, evMouseButtonReleased, getEventManager());
}


/**
 * @brief Triebwerke einschalten
 */
void ShipInputSystem::powerEngines() {
    float percentage = 0;
    percentage +=  pressedKeys.find(Keyboard::W) != pressedKeys.end();
    percentage -=  pressedKeys.find(Keyboard::S) != pressedKeys.end();
    EventMessage * message = new EventMessage(cmPowerEngines);
    message->value = percentage;
    componentList[0].notifyListeners(message);
    delete message;
}



Handle *ShipInputSystem::createComponent(ShipInputSettings settings) {
    return GameSystem::createComponent(settings);
}


/**
 * @brief Schiff als Listener registrieren
 * @param shipHandle Das Schiffhandle
 */
void ShipInputSystem::registerShipAsListener(Handle *shipHandle) {
    registerComponentAsListener(0, cmPowerEngines, shipHandle->id,
                                shipHandle->system->getEventManager());
    registerComponentAsListener(0, cmRotateTo, shipHandle->id,
                                shipHandle->system->getEventManager());
    registerComponentAsListener(0, cmStopRotating, shipHandle->id,
                                shipHandle->system->getEventManager());
    registerComponentAsListener(0, cmAimAt, shipHandle->id,
                                shipHandle->system->getEventManager());
    registerComponentAsListener(0, cmOpenFire, shipHandle->id,
                                shipHandle->system->getEventManager());
    registerComponentAsListener(0, cmCeaseFire, shipHandle->id,
                                shipHandle->system->getEventManager());
}


void ShipInputSystem::update(float dt) {
    GameSystem::update(dt);
}


/**
 * @copydoc GameSystem::notify
 * Verarbeitet Nutzereingaben
 */
void ShipInputSystem::notify(EventMessage *message){
    switch (message->event) {
    case evKeyPressed: {
        EventKeyMessage* keyMessage = (EventKeyMessage*) message;
        if (keyMessage->key == Keyboard::W || keyMessage->key == Keyboard::S) {
            pressedKeys.insert(keyMessage->key);
            powerEngines();
        } else if (keyMessage->key == Keyboard::G) {
            EventMessage* telMessage = new EventMessage(cmStartTeleport);
            componentList[0].notifyListeners(telMessage);
            delete telMessage;
        }
        break;
    }
    case evKeyReleased: {
        EventKeyMessage* keyMessage = (EventKeyMessage*) message;
        if (keyMessage->key == Keyboard::W || keyMessage->key == Keyboard::S) {
            pressedKeys.erase(keyMessage->key);
            powerEngines();
        }
        break;
    }
    case evMouseMoved: {
        EventMouseMessage* mouseMessage = (EventMouseMessage*) message;
        EventPosMessage* posMessage = new EventPosMessage;
        posMessage->event = cmAimAt;
        posMessage->pos = mouseMessage->pos;
        componentList[0].notifyListeners(posMessage);
        if (rotating) {
            posMessage->event = cmRotateTo;
            componentList[0].notifyListeners(posMessage);
        }
        delete posMessage;
        break;
    }
    case evMouseButtonPressed: {
        EventMouseMessage* mouseMessage = (EventMouseMessage*) message;
        if (mouseMessage->button == Mouse::Left) {
            rotating = true;
            EventPosMessage* posMessage = new EventPosMessage;
            posMessage->event = cmRotateTo;
            posMessage->pos = mouseMessage->pos;
            componentList[0].notifyListeners(posMessage);
            delete posMessage;
        } else if (mouseMessage->button == Mouse::Right) {
            EventMessage* fireMessage = new EventMessage(cmOpenFire);
            componentList[0].notifyListeners(fireMessage);
            delete fireMessage;
        }
        break;
    }
    case evMouseButtonReleased: {
        EventMouseMessage* mouseMessage = (EventMouseMessage*) message;
        if (mouseMessage->button == Mouse::Left) {
            rotating = false;
            EventMessage* stopMessage = new EventMessage(cmStopRotating);
            componentList[0].notifyListeners(stopMessage);
            delete stopMessage;
        } else if (mouseMessage->button == Mouse::Right) {
            EventMessage* fireMessage = new EventMessage(cmCeaseFire);
            componentList[0].notifyListeners(fireMessage);
            delete fireMessage;
        }
        break;
    }
    }

    delete message;;
}


ShipInputSystem::ShipInputSystem(ShipInputSettings settings, InputSystem& inputSystem,
                                 CameraSystem& cameraSystem)
    : inputSystem(inputSystem), cameraSystem(cameraSystem){
    singleton = createComponent(settings);
    registerAsListener();
}
