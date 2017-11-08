#include "weaponcomponent.h"
#include <math.h>

void WeaponComponent::notify(EventMessage *message) {
    switch(message->event) {
    case cmOpenFire: {
        notifyListeners(message);
        break;
    }

    case cmCeaseFire: {
        notifyListeners(message);
        break;
    }

    case cmAimAt: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        posMessage->event = cmRotateTo;
        posMessage->torque = 12;
        notifyListeners(posMessage);
        break;
    }

    case evEnergyStatus: {
        notifyListeners(message);
        break;
    }

    case evEnergyUsed: {
        notifyListeners(message);
        break;
    }

    case cmUpgrade: {
        EventUpgradeMessage* upMessage = (EventUpgradeMessage*) message;

        if (upMessage->slot == settings.slot) {
            notifyListeners(message);
        }

        break;
    }

    case cmActivate: {
        notifyListeners(message);
        break;
    }

    case cmDeactivate: {
        notifyListeners(message);
        break;
    }
    }

    delete message;;
}

WeaponComponent::WeaponComponent(WeaponSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {

    Event events[8] = {cmOpenFire, cmCeaseFire, cmRotateTo, evEnergyStatus, evEnergyUsed, cmUpgrade,
                      cmActivate, cmDeactivate};
    initializeEvents(events, 8);
}
