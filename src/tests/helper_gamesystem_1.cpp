#include "helper_gamesystem_1.h"

void Helper_GameSystem_1::setSendingMessage(unsigned int id, std::string text) {
    componentList[indices[id]].sendingMessage = text;
}


std::string Helper_GameSystem_1::getSendingMessage(unsigned int id) {
    return componentList[indices[id]].sendingMessage;
}


std::string Helper_GameSystem_1::getReceivedMessage(unsigned int id) {
    return componentList[indices[id]].receivedMessage;
}


std::string Helper_GameSystem_1::getReceivedMessage() {
    return receivedMessage;
}


void Helper_GameSystem_1::resetReceivedMessage(unsigned int id) {
    componentList[indices[id]].receivedMessage = "";
}


void Helper_GameSystem_1::resetReceivedMessage() {
    receivedMessage = "";
}


/**
 * @brief Gibt die EventListenerMap einer Komponente zurück
 * @param id Die ID der Komponente
 * @return Die EventListenerMap
 */
std::map<Event, std::vector<Listener>>
    Helper_GameSystem_1::getComponentEventListenerMap(unsigned int id){

    return *(getComponent(id)->getEventListenerMap());
}


/**
 * @brief Gibt ein Array mit den jeweiligen "settings.number"-Werten der Komponenten zurück
 * @param expectedLength die erwartete Länge des Arrays
 * @return Das Array
 *
 * Wird für den GameSystem-Unittest benutzt
 */
int* Helper_GameSystem_1::getComponentArray(unsigned int expectedLength) {
    //if (expectedLength != componentList.size())
    //   return nullptr;

    int* array = new int[expectedLength];

    for (unsigned int i = 0; i < expectedLength; i++) {
        array[i] = componentList[i].settings.number;
    }

    return array;
}


void Helper_GameSystem_1::update(float dt) {
    GameSystem::update(dt);

    EventTestMessage* message = new EventTestMessage();

    for (unsigned int i = 0; i < componentList.size(); i++) {
        message->text = componentList[i].sendingMessage;
        componentList[i].notifyListeners(message);
    }

    delete message;
    GameSystem::update(dt);
}


void Helper_GameSystem_1::notify(EventMessage* message) {

    if (message->event == evTestEvent) {
        EventTestMessage * testMessage = (EventTestMessage* ) message;
        receivedMessage = testMessage->text;
    }


    delete message;
}




Helper_GameSystem_1::Helper_GameSystem_1() : GameSystem() {

}
