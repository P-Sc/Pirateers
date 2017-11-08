/**
 * @file helper_component_1.h
 */

#ifndef HELPER_COMPONENT_1_H
#define HELPER_COMPONENT_1_H

#include "base/component.h"
#include "base/settings.h"

/**
 * @struct Helper_Settings_1
 * @brief Helferklasse für den GameSystem-Unittest
 */
struct Helper_Settings_1 : Settings {
    int number;
    bool listener = false;
    bool sender = false;
    std::string senderMessage;
};


/**
 * @class Helper_Component_1
 * @brief Helferklasse für den GameSystem-Unittest
 */
class Helper_Component_1 : public Component
{
public:
	std::string sendingMessage = "";
	std::string receivedMessage = "";
	Helper_Settings_1 settings;

	virtual void notify(EventMessage * message);

    Helper_Component_1(Helper_Settings_1 settings, Handle* handle);
    ~Helper_Component_1();
};

#endif // HELPER_COMPONENT_1_H
