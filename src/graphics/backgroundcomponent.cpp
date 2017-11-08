#include "backgroundcomponent.h"

void BackgroundComponent::notify(EventMessage * message) {

    delete message;;
}

BackgroundComponent::BackgroundComponent(BackgroundSettings settings, Handle* handle)
    : Component(settings, handle) {

    this->settings = settings;
}
