#include "mainmenucomponent.h"

MainMenuComponent::MainMenuComponent(Settings settings, Handle* handle)
    : Component(settings, handle) {

    Event events[3] = {evMainMenuOpened, evMainMenuClosed, cmPlaySound};
    initializeEvents(events, 3);
}
