#include "shipinputcomponent.h"

ShipInputComponent::ShipInputComponent(ShipInputSettings settings, Handle* handle)
    : Component(settings, handle) {

    Event events[7] = {cmPowerEngines, cmRotateTo, cmStopRotating, cmAimAt, cmOpenFire, cmCeaseFire,
                      cmStartTeleport};
    initializeEvents(events, 7);
}
