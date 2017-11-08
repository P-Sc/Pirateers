/**
 * @file mainmenucomponent.h
 */
#ifndef MAINMENUCOMPONENT_H
#define MAINMENUCOMPONENT_H

#include "base/component.h"
#include "base/settings.h"

/**
 * @class MainMenuComponent
 * @brief Dummy-Klasse zum Versenden von Nachrichten
 */
class MainMenuComponent : public Component {
public:
    MainMenuComponent(Settings settings, Handle* handle);
};

#endif // MAINMENUCOMPONENT_H
