#include "shipcomponent.h"


/**
 * @brief Versendet cmApplyForce-Nachricht
 * @param percentage Prozentualer Anteil des maximalen Antriebs
 */
void ShipComponent::applyThrust(float percentage) {
    float thrust = 0;

    if (percentage > 0) {
        thrust = settings.propulsion * percentage;
    } else if (percentage <= 0) {
        thrust = settings.propulsion * percentage * 0.4;
    }

    EventPosMessage* posMessage = new EventPosMessage();
    posMessage->event = cmApplyForce;
    posMessage->force = thrust;
    notifyListeners(posMessage);
    delete posMessage;
}

/**
 * @copydoc Component::notify
 * - ::evMove Position speichern und weiterleiten
 * - ::cmPowerEngines Triebwerke einschalten
 * - ::cmRotateTo Weiterleiten
 * - ::cmStopRotating Weiterleiten
 * - ::cmAimAt Weiterleiten
 * - ::cmOpenFire Weiterleiten
 * - ::cmCeaseFire Weiterleiten
 * - ::evDestroyed Als Zerstört markieren
 * - ::evShield Weiterleiten
 * - ::evEnergyStatus Weiterleiten
 * - ::cmUpgrade Weiterleiten
 * - ::cmRepair Weiterleiten
 * - ::cmActivate Aktivieren und weiterleiten
 * - ::cmDeactivate Deaktivieren und weiterleiten
 */
void ShipComponent::notify(EventMessage* message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        pos = posMessage->pos;
        notifyListeners(message);
        break;
    }

    case cmPowerEngines: {
        applyThrust(message->value);
        notifyListeners(message);
        break;
    }

    case cmRotateTo: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        posMessage->torque = settings.maxTorque;
        notifyListeners(posMessage);
        break;
    }

    case cmStopRotating: {
        notifyListeners(message);
        break;
    }

    case cmAimAt: {
        notifyListeners(message);
        break;
    }

    case cmOpenFire: {
        notifyListeners(message);
        break;
    }

    case cmCeaseFire: {
        notifyListeners(message);
        break;
    }

    case evDestroyed: {
        exploding = true;
        break;
    }

    case evShield: {
        notifyListeners(message);
        break;
    }

    case evEnergyStatus: {
        notifyListeners(message);
        break;
    }

    case cmUpgrade: {
        notifyListeners(message);
        break;
    }

    case cmRepair: {
        notifyListeners(message);
        break;
    }

    case cmActivate: {
        settings.active = true;
        notifyListeners(message);
        break;
    }

    case cmDeactivate: {
        settings.active = false;
        notifyListeners(message);
        break;
    }
    }

    delete message;;
}


ShipComponent::ShipComponent(ShipSettings settings, Handle* handle)
    : Component(settings, handle) {
    this->settings = settings;

    Event events[15] = {evMove, cmApplyForce, cmRotateTo, cmStopRotating, cmAimAt, cmOpenFire,
                        cmCeaseFire, evShield, evEnergyStatus, evDestroyed, cmPowerEngines,
                        cmUpgrade, cmRepair, cmActivate, cmDeactivate,
                       };
    initializeEvents(events, 15);
}
