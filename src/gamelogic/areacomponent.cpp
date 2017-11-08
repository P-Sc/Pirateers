#include "areacomponent.h"

AreaComponent::AreaComponent(Settings settings, Handle* handle)
    : Component(settings, handle) {

    Event events[3] = {evAreaChanged, evPlayerSet, evNoPlayerSet};
    initializeEvents(events, 3);
}
