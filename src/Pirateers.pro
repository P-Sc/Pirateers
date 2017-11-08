CONFIG += c++11

TARGET = Pirateers
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

INCLUDEPATH += /usr/local/include/SFML/
INCLUDEPATH += /usr/include/Box2D/
#INCLUDEPATH += $$PWD/include/

#DEPENDPATH += /usr/include/SFML/
#DEPENDPATH += /usr/include/Box2D/

#LIBS += -L$$PWD/lib -lBox2D
LIBS += -L/usr/local/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBS += -L/usr/lib/x86_64-linux-gnu/ -lboost_system -lboost_filesystem
LIBS += -L/usr/lib/x86_64-linux-gnu/ -lBox2D

SOURCES += main.cpp \
    utils/fixedindexarray.cpp \
    events/eventmanager.cpp \
    entities/player.cpp \
    tests/test_fixedindexarray.cpp \
    tests/unittest.cpp \
    tests/testlogger.cpp \
    tests/completetest.cpp \
    tests/test_gamesystem.cpp \
    tests/helper_gamesystem_1.cpp \
    tests/helper_component_1.cpp \
    tests/test_eventmanager.cpp \
    utils/shipparser.cpp \
    graphics/graphicssystem.cpp \
    graphics/graphicscomponent.cpp \
    input/inputcomponent.cpp \
    ship/shipcomponent.cpp \
    physics/physicscomponent.cpp \
    base/component.cpp \
    base/gamesystem.cpp \
    input/inputsystem.cpp \
    physics/physicssystem.cpp \
    ship/shipsystem.cpp \
    debug/modelcomponent.cpp \
    debug/modeldisplaysystem.cpp \
    camera/cameracomponent.cpp \
    camera/camerasystem.cpp \
    graphics/backgroundcomponent.cpp \
    graphics/backgroundsystem.cpp \
    graphics/textures.cpp \
    ship/weaponcomponent.cpp \
    ship/weaponsystem.cpp \
    ship/ammocomponent.cpp \
    ship/ammosystem.cpp \
    input/shipinputcomponent.cpp \
    input/shipinputsystem.cpp \
    gui/tagcomponent.cpp \
    gui/tagsystem.cpp \
    ship/weaponloader.cpp \
    ship/shieldcomponent.cpp \
    ship/shieldsystem.cpp \
    sound/sounds.cpp \
    sound/soundcomponent.cpp \
    sound/soundsystem.cpp \
    graphics/lightcomponent.cpp \
    graphics/lightsystem.cpp \
    camera/camerashakecomponent.cpp \
    camera/camerashakesystem.cpp \
    ship/explosioncomponent.cpp \
    ship/explosionsystem.cpp \
    ship/energycomponent.cpp \
    ship/energysystem.cpp \
    gamelogic/aicomponent.cpp \
    gamelogic/aisystem.cpp \
    entities/aliendrone.cpp \
    graphics/stardustsystem.cpp \
    entities/enemyship.cpp \
    gamelogic/rewardcomponent.cpp \
    gamelogic/rewardsystem.cpp \
    ship/engineeffectcomponent.cpp \
    ship/engineeffectsystem.cpp \
    gamelogic/shopcomponent.cpp \
    gamelogic/shopsystem.cpp \
    gui/statusinformationsystem.cpp \
    gamelogic/areasystem.cpp \
    entities/bretoniafighter.cpp \
    entities/bretoniafreighter.cpp \
    entities/bretoniagunship.cpp \
    gamelogic/areacomponent.cpp \
    entities/banditdrone.cpp \
    entities/alienfighter.cpp \
    entities/xurufreighter.cpp \
    entities/banditfreighter.cpp \
    entities/taulonfreighter.cpp \
    entities/xurugunship.cpp \
    sound/musicsystem.cpp \
    gamelogic/teleportcomponent.cpp \
    gamelogic/teleportsystem.cpp \
    gui/mainmenusystem.cpp \
    gui/mainmenucomponent.cpp \
    utils/highscoreloader.cpp

HEADERS += \
    handle.h \
    exceptions/fileopenerror.h \
    utils/fixedindexarray.h \
    events/eventmanager.h \
    events/messages.h \
    events/listener.h \
    entities/player.h \
    tests/test_fixedindexarray.h \
    tests/unittest.h \
    tests/testlogger.h \
    tests/completetest.h \
    tests/test_gamesystem.h \
    tests/helper_gamesystem_1.h \
    tests/helper_component_1.h \
    tests/test_eventmanager.h \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml_iterators.hpp \
    rapidxml/rapidxml_print.hpp \
    rapidxml/rapidxml_utils.hpp \
    utils/shipparser.h \
    base/component.h \
    graphics/graphicscomponent.h \
    input/inputcomponent.h \
    physics/physicscomponent.h \
    ship/shipcomponent.h \
    base/gamesystem.h \
    graphics/graphicssystem.h \
    input/inputsystem.h \
    base/isystem.h \
    physics/physicssystem.h \
    ship/shipsystem.h \
    graphics/graphicssettings.h \
    physics/physicssettings.h \
    base/settings.h \
    ship/shipsettings.h \
    debug/modelsettings.h \
    debug/modelcomponent.h \
    debug/modeldisplaysystem.h \
    camera/cameracomponent.h \
    camera/camerasystem.h \
    graphics/backgroundsettings.h \
    graphics/backgroundcomponent.h \
    graphics/backgroundsystem.h \
    graphics/textures.h \
    ship/weaponsettings.h \
    ship/weaponcomponent.h \
    ship/weaponsystem.h \
    ship/ammosettings.h \
    ship/ammocomponent.h \
    ship/ammosystem.h \
    input/shipinputsettings.h \
    input/shipinputcomponent.h \
    input/shipinputsystem.h \
    physics/entitycategory.h \
    gui/tagsettings.h \
    gui/tagcomponent.h \
    gui/tagsystem.h \
    ship/projectile.h \
    ship/weaponloader.h \
    ship/weapon.h \
    ship/shieldsettings.h \
    ship/shieldcomponent.h \
    ship/shieldsystem.h \
    sound/sounds.h \
    sound/soundsettings.h \
    sound/soundcomponent.h \
    sound/soundsystem.h \
    graphics/lightsettings.h \
    graphics/lightcomponent.h \
    graphics/lightsystem.h \
    camera/camerashakesettings.h \
    camera/camerashakecomponent.h \
    camera/camerashakesystem.h \
    ship/explosionsettings.h \
    ship/explosioncomponent.h \
    ship/explosionsystem.h \
    ship/energysettings.h \
    ship/energycomponent.h \
    ship/energysystem.h \
    gamelogic/aisettings.h \
    gamelogic/aicomponent.h \
    gamelogic/aisystem.h \
    entities/aliendrone.h \
    graphics/stardustsystem.h \
    entities/enemyship.h \
    gamelogic/rewardsettings.h \
    gamelogic/rewardcomponent.h \
    gamelogic/rewardsystem.h \
    ship/engineeffectsettings.h \
    ship/engineeffectcomponent.h \
    ship/engineeffectsystem.h \
    gamelogic/shopsettings.h \
    gamelogic/shopcomponent.h \
    gamelogic/shopsystem.h \
    gui/statusinformationsystem.h \
    gamelogic/areasystem.h \
    entities/bretoniafighter.h \
    entities/bretoniafreighter.h \
    entities/bretoniagunship.h \
    gamelogic/areacomponent.h \
    entities/banditdrone.h \
    entities/alienfighter.h \
    entities/xurufreighter.h \
    entities/banditfreighter.h \
    entities/taulonfreighter.h \
    entities/xurugunship.h \
    sound/musicsystem.h \
    gamelogic/teleportcomponent.h \
    gamelogic/teleportsystem.h \
    gui/mainmenusystem.h \
    gui/mainmenucomponent.h \
    utils/highscoreloader.h


QMAKE_CXXFLAGS += -std=c++11 -gdwarf-4 -fvar-tracking -Wno-switch -Wno-unused-parameter
