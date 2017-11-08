#include "helper_component_1.h"
#include <iostream>

void Helper_Component_1::notify(EventMessage * message) {
    if (message->event == evTestEvent) {
        EventTestMessage* testMessage = (EventTestMessage*) message;
        receivedMessage = testMessage->text;
    }
}


Helper_Component_1::Helper_Component_1(Helper_Settings_1 settings, Handle* handle)
    : Component(settings, handle) {
    this->settings = settings;
    Event events[1] = {evTestEvent};
    initializeEvents(events, 1);
}

/**
 * @brief Destruktor
 */
Helper_Component_1::~Helper_Component_1() {
    // Debug
    //std::cout << "Component deleted with Number " + std::to_string(this->settings.number);
    //std::cout << std::endl;
    this->settings.number = 1;
}
