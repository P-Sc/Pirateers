#include "energycomponent.h"


/**
 * @brief Versendet evEnergyStatus-Nachrichten.
 */
void EnergyComponent::reportChange() {
    EventMessage* message = new EventMessage(evEnergyStatus);
    message->value = energy;
    message->value2 = settings.maxEnergy;
    notifyListeners(message);
    delete message;
}

/**
 * @brief Regeneriert Energie
 * @param value Wert, der regeneriert werden soll.
 * @return True, falls sich Energie verändert hat.
 */
bool EnergyComponent::regenEnergy(float value) {
    int oldValue = energy;
    energy = std::min(energy + value, (float) settings.maxEnergy);

    if (oldValue == energy) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Aktualisiert Komponente
 * @param dt Zeit in ms.
 */
void EnergyComponent::tick(float dt) {
    if (regenEnergy(settings.regenPerSecond * dt / 1000.f)) {
        changed = true;
    }

    if (changed) {
        reportChange();
        changed = false;
    }
}

/**
 * @copydoc Component::notify
 * - ::evEnergyUsed Energie verbrauchen
 * - ::cmUpgrade Upgraden
 */
void EnergyComponent::notify(EventMessage* message) {
    switch (message->event) {
    case evEnergyUsed: {
        energy = std::max(energy - message->value, 0.f);
        break;
    }

    case cmUpgrade: {
        EventUpgradeMessage* upMessage = (EventUpgradeMessage*) message;

        if (upMessage->upgrade == "energy") {
            settings.maxEnergy += upMessage->value;
            settings.regenPerSecond += settings.regenPerSecond
                                       * upMessage->value / settings.maxEnergy;
        }

        break;
    }
    }

    delete message;;
}

EnergyComponent::EnergyComponent(EnergySettings settings, Handle* handle)
    : Component(settings, handle) {

    this->settings = settings;
    energy = settings.maxEnergy - 1;

    Event events[1] = {evEnergyStatus};
    initializeEvents(events, 1);
}
