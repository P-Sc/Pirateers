#include "inputcomponent.h"
#include "base/settings.h"


InputComponent::InputComponent(Settings settings, Handle* handle) : Component(settings, handle) {
    Event events[8] = {evKeyPressed, evKeyReleased, evMouseMoved,
                       evMouseButtonPressed, evMouseButtonReleased, evMouseWheelScrolled,
                       evWindowClosed, evWindowResized};
    initializeEvents(events, 8);

}
