/**
 * @file helper_gamesystem_1.h
 */

#ifndef HELPER_GAMESYSTEM_1_H
#define HELPER_GAMESYSTEM_1_H

#include "base/gamesystem.h"
#include "helper_component_1.h"

/**
 * @class Helper_GameSystem_1
 * @brief Helferklasse für den GameSystem-Unittest
 */
class Helper_GameSystem_1 : public GameSystem<Helper_Component_1, Helper_Settings_1>
{
private:
    std::string receivedMessage;
public:
    void setSendingMessage(unsigned int id, std::string text);
    std::string getSendingMessage(unsigned int id);
    std::string getReceivedMessage(unsigned int id);
    std::string getReceivedMessage();
    void resetReceivedMessage(unsigned int id);
    void resetReceivedMessage();
    std::map<Event, std::vector<Listener>> getComponentEventListenerMap(unsigned int id);
    int* getComponentArray(unsigned int expectedLength);
    virtual void update(float dt);
    virtual void notify(EventMessage* message);
    Helper_GameSystem_1();
};

#endif // HELPER_GAMESYSTEM_1_H
