#include "cameracomponent.h"

CameraComponent::CameraComponent(Settings settings, Handle* handle)
    : Component(settings, handle) {

    Event events[2] = {evCameraChanged, evMouseMoved};
    initializeEvents(events, 2);
}
