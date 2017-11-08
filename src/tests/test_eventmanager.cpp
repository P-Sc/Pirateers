#include "test_eventmanager.h"
#include "tests/helper_gamesystem_1.h"
#include "tests/helper_component_1.h"

typedef std::map<Event, std::vector<Listener>> EventListenerMap;

/**
 * @brief Testen von Cross-Registrations (d.h. mit verschiedene GameSystem-Instanzen)
 *        von Komponenten.
 */
void Test_EventManager::test1() {
    log ("Testing: Cross-Registrations (different GameSystem instances) with Components");
    currentTestCase = 1;

    /*
     * listenerComponent1 registriert sich bei senderComponent1 und senderComponent2.
     * listenerComponent2 registriert sich nur bei senderComponent1.
     */
    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              listenerComponent2->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              listenerComponent1->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent2->id, evTestEvent,
                                              listenerComponent1->id, listenerSystem->getEventManager());

    EventListenerMap map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    EventListenerMap map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);

    std::vector<Listener>& listeners1 = map1.at(evTestEvent);
    std::vector<Listener>& listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 2 || listeners2.size() != 1) {
        reportFailure("List of listeners has wrong size.");
        return;
    }

    // IDs überprüfen
    if (listeners1[0].id != listenerComponent2->id || listeners1[1].id != listenerComponent1->id
            || listeners2[0].id != listenerComponent1->id) {

        reportFailure("Listener entries have wrong IDs");
        return;
    }

    // Manager-Adressen überprüfen
    if (listeners1[0].destinationManager != listenerSystem->getEventManager()
            || listeners1[1].destinationManager != listenerSystem->getEventManager()
            || listeners2[0].destinationManager != listenerSystem->getEventManager()) {

        reportFailure("Listener entries have wrong EventManager addresses");
        return;
    }

    reportSuccess();
}

/**
 * @brief Testen von Registrierungen mit gleichem GameSystem
 *        von Komponenten.
 */
void Test_EventManager::test2() {
    log ("Testing: Registrations on the same GameSystem instance with Components");
    currentTestCase = 2;

    /*
     * senderComponent1 registriert sich bei senderComponent2 und andersherum.
     */
    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              senderComponent2->id, senderSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent2->id, evTestEvent,
                                              senderComponent1->id, senderSystem->getEventManager());

    EventListenerMap map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    EventListenerMap map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);

    std::vector<Listener>& listeners1 = map1.at(evTestEvent);
    std::vector<Listener>& listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 1 || listeners2.size() != 1) {
        reportFailure("List of listeners has wrong size.");
        return;
    }

    // IDs überprüfen
    if (listeners1[0].id != senderComponent2->id || listeners2[0].id != listenerComponent1->id) {

        reportFailure("Listener entries have wrong IDs");
        return;
    }

    // Manager-Adressen überprüfen
    if (listeners1[0].destinationManager != senderSystem->getEventManager()
            || listeners2[0].destinationManager != senderSystem->getEventManager()) {

        reportFailure("Listener entries have wrong EventManager addresses");
        return;
    }

    reportSuccess();
}


/**
 * @brief Testet Registrierung eines GameSystem als Listener
 */
void Test_EventManager::test3() {
    log ("Testing: Cross-Registrations (different GameSystem instances) with GameSystems");
    currentTestCase = 3;
    Helper_GameSystem_1 * listenerSystem2 = new Helper_GameSystem_1();

    /*
     * listenerSystem registriert sich bei senderComponent1 und senderComponent2.
     * listenerSystem2 registriert sich bei senderComponent1
     */
    senderSystem->registerSystemAsListener(senderComponent1->id, evTestEvent,
                                           listenerSystem->getEventManager());
    senderSystem->registerSystemAsListener(senderComponent1->id, evTestEvent,
                                           listenerSystem2->getEventManager());
    senderSystem->registerSystemAsListener(senderComponent2->id, evTestEvent,
                                           listenerSystem->getEventManager());

    EventListenerMap map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    EventListenerMap map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);

    std::vector<Listener> listeners1 = map1.at(evTestEvent);
    std::vector<Listener> listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 2 || listeners2.size() != 1) {
        reportFailure("List of listeners has wrong size.");
        return;
    }

    // Überprüfen, ob Einträge als GameSystem-Listener markiert sind
    if (!listeners1[0].gameSystemListener || !listeners1[1].gameSystemListener
            || !listeners2[0].gameSystemListener) {

        reportFailure("Listener not marked as GameSystems");
        return;
    }

    // Manager-Adressen überprüfen
    if (listeners1[0].destinationManager != listenerSystem->getEventManager()
            || listeners1[1].destinationManager != listenerSystem2->getEventManager()
            || listeners2[0].destinationManager != listenerSystem->getEventManager()) {

        reportFailure("Listener entries have wrong EventManager addresses");
        return;
    }

    delete listenerSystem2;

    reportSuccess();
}


/**
 * @brief Testet Deregistrierung einer Komponente als Listener
 */
void Test_EventManager::test4() {
    log ("Testing: Deregistrations with Components");
    currentTestCase = 4;

    /*
     * listenerComponent1 registriert sich bei senderComponent1 und senderComponent2.
     * listenerComponent2 registriert sich bei senderComponent1.
     * senderComponent2 registriert sich bei senderComponent1.
     */
    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              listenerComponent2->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              listenerComponent1->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent2->id, evTestEvent,
                                              listenerComponent1->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              senderComponent2->id, senderSystem->getEventManager());


    EventListenerMap map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    EventListenerMap map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);
    std::vector<Listener> listeners1 = map1.at(evTestEvent);
    std::vector<Listener> listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 3 || listeners2.size() != 1) {
        reportFailure("Lists of listeners have wrong size after registration");
        return;
    }

    /*
     * listenerComponent1 bei senderComponent2 abmelden (0 übrig)
     * listenerComponent2 bei senderComponent1 abmelden
     * senderComponent2 bei senderComponent2 abmelden (1 übrig)
     */


    listenerSystem->eraseComponentRegistration(senderComponent1->id, evTestEvent,
                                                                listenerComponent2->id,
                                                                senderSystem->getEventManager());

    listenerSystem->eraseComponentRegistration(senderComponent2->id, evTestEvent,
                                                                listenerComponent1->id,
                                                                senderSystem->getEventManager());

    senderSystem->eraseComponentRegistration(senderComponent1->id, evTestEvent,
                                                                senderComponent2->id,
                                                                senderSystem->getEventManager());

    map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);
    listeners1 = map1.at(evTestEvent);
    listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 1 || listeners2.size() != 0) {
        reportFailure("Lists of listeners have wrong size after deregistrations");
        return;
    }


    /*
     * listenerComponent2 wieder bei senderComponent1 registrieren.
     * senderComponent1 bei senderComponent2 registrieren (neu)
     */

    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              listenerComponent2->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent2->id, evTestEvent,
                                              senderComponent1->id, senderSystem->getEventManager());


    map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);
    listeners1 = map1.at(evTestEvent);
    listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 2 || listeners2.size() != 1) {
        reportFailure("Lists of listeners habe wrong size after re-registrations");
        return;
    }


    // IDs überprüfen
    if (listeners1[0].id != listenerComponent1->id || listeners1[1].id != listenerComponent2->id
            || listeners2[0].id != senderComponent1->id) {

        reportFailure("Listener entries have wrong IDs");
        return;
    }

    // Manager-Adressen überprüfen
    if (listeners1[0].destinationManager != listenerSystem->getEventManager()
            || listeners1[1].destinationManager != listenerSystem->getEventManager()
            || listeners2[0].destinationManager != senderSystem->getEventManager()) {

        reportFailure("Listener entries have wrong EventManager addresses");
        return;
    }

    reportSuccess();
}


/**
 * @brief Testet Deregistrierung eines GameSystem als Listener
 */
void Test_EventManager::test5() {
    log ("Testing: Deregistrations with GameSystems");
    currentTestCase = 5;

    Helper_GameSystem_1 * listenerSystem2 = new Helper_GameSystem_1();

    /*
     * listenerSystem registriert sich bei senderComponent1 und senderComponent2.
     * listenerSystem2 registriert sich bei senderComponent1
     */
    senderSystem->registerSystemAsListener(senderComponent1->id, evTestEvent,
                                           listenerSystem->getEventManager());
    senderSystem->registerSystemAsListener(senderComponent1->id, evTestEvent,
                                           listenerSystem2->getEventManager());
    senderSystem->registerSystemAsListener(senderComponent2->id, evTestEvent,
                                           listenerSystem->getEventManager());

    EventListenerMap map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    EventListenerMap map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);
    std::vector<Listener> listeners1 = map1.at(evTestEvent);
    std::vector<Listener> listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 2 || listeners2.size() != 1) {
        reportFailure("Lists of listeners have wrong size after registration");
        return;
    }

    /*
     * listenerSystem meldet sich bei senderComponent2 ab
     * listenerSystem2 meldet sich bei senderComponent1 ab
     */
    listenerSystem->eraseSystemRegistration(senderComponent2->id, evTestEvent,
                                            senderSystem->getEventManager());
    listenerSystem2->eraseSystemRegistration(senderComponent1->id, evTestEvent,
                                            senderSystem->getEventManager());

    map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);
    listeners1 = map1.at(evTestEvent);
    listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 1 || listeners2.size() != 0) {
        reportFailure("Lists of listeners have wrong size after registration");
        return;
    }

    senderSystem->registerSystemAsListener(senderComponent1->id, evTestEvent,
                                           listenerSystem2->getEventManager());
    senderSystem->registerSystemAsListener(senderComponent2->id, evTestEvent,
                                           listenerSystem2->getEventManager());

    map1 = senderSystem->getComponentEventListenerMap(senderComponent1->id);
    map2 = senderSystem->getComponentEventListenerMap(senderComponent2->id);
    listeners1 = map1.at(evTestEvent);
    listeners2 = map2.at(evTestEvent);

    // Listengröße überprüfen
    if (listeners1.size() != 2 || listeners2.size() != 1) {
        reportFailure("Lists of listeners have wrong size after registration");
        return;
    }

    // Überprüfen, ob Einträge als GameSystem-Listener markiert sind
    if (!listeners1[0].gameSystemListener || !listeners1[1].gameSystemListener
            || !listeners2[0].gameSystemListener) {

        reportFailure("Listener not marked as GameSystems");
        return;
    }

    // Manager-Adressen überprüfen
    if (listeners1[0].destinationManager != listenerSystem->getEventManager()
            || listeners1[1].destinationManager != listenerSystem2->getEventManager()
            || listeners2[0].destinationManager != listenerSystem2->getEventManager()) {

        reportFailure("Listener entries have wrong EventManager addresses");
        return;
    }

    delete listenerSystem2;

    reportSuccess();
}


/**
 * @brief Testet Benachrichtung an eine Komponente
 */
void Test_EventManager::test6() {
    log ("Testing: Notifiyng components");
    currentTestCase = 6;


    /*
     * listenerComponent1 registriert sich bei senderComponent1 und senderComponent2.
     * listenerComponent2 registriert sich bei senderComponent1.
     * senderComponent2 registriert sich bei senderComponent1.
     */
    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              listenerComponent2->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              listenerComponent1->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent2->id, evTestEvent,
                                              listenerComponent1->id, listenerSystem->getEventManager());

    senderSystem->registerComponentAsListener(senderComponent1->id, evTestEvent,
                                              senderComponent2->id, senderSystem->getEventManager());

    senderSystem->setSendingMessage(senderComponent1->id, "Message A");
    senderSystem->setSendingMessage(senderComponent2->id, "Message B");

    senderSystem->update(1.f);
    listenerSystem->update(1.f);

    // Erhaltene Nachrichten überprüfen
    if (listenerSystem->getReceivedMessage(listenerComponent2->id) != "Message A"
            || listenerSystem->getReceivedMessage(listenerComponent1->id) != "Message B"
            || senderSystem->getReceivedMessage(senderComponent2->id) != "Message A"
            || senderSystem->getReceivedMessage(senderComponent1->id) != "") {

        reportFailure("Invalid or no messages received");
        return;
    }


    reportSuccess();
}


/**
 * @brief Testet Benachrichtigung an ein GameSystem
 */
void Test_EventManager::test7() {
    log ("Testing: ");
    currentTestCase = 7;

    Helper_GameSystem_1 * listenerSystem2 = new Helper_GameSystem_1();

    /*
     * listenerSystem registriert sich bei senderComponent1 und senderComponent2.
     * listenerSystem2 registriert sich bei senderComponent1
     */
    senderSystem->registerSystemAsListener(senderComponent1->id, evTestEvent,
                                           listenerSystem->getEventManager());
    senderSystem->registerSystemAsListener(senderComponent1->id, evTestEvent,
                                           listenerSystem2->getEventManager());
    senderSystem->registerSystemAsListener(senderComponent2->id, evTestEvent,
                                           listenerSystem->getEventManager());


    senderSystem->setSendingMessage(senderComponent1->id, "Message A");
    senderSystem->setSendingMessage(senderComponent2->id, "Message B");

    senderSystem->update(1.f);
    listenerSystem->update(1.f);
    listenerSystem2->update(1.f);

    // Erhaltene Nachrichten überprüfen
    if (listenerSystem->getReceivedMessage() != "Message B"
            || listenerSystem2->getReceivedMessage() != "Message A"
            || senderSystem->getReceivedMessage() != "") {

        reportFailure("Invalid or no messages received");
        return;
    }

    delete listenerSystem2;
    reportSuccess();
}



void Test_EventManager::startTests() {
    init();
    test1();
    cleanUp();

    init();
    test2();
    cleanUp();

    init();
    test3();
    cleanUp();

    init();
    test4();
    cleanUp();

    init();
    test5();
    cleanUp();

    init();
    test6();
    cleanUp();

    init();
    test7();
    cleanUp();
}


void Test_EventManager::init() {
    Helper_Settings_1 settings;

    listenerSystem = new Helper_GameSystem_1();
    senderSystem = new Helper_GameSystem_1();

    settings.listener = true;
    settings.number = 1;
    listenerComponent1 = listenerSystem->createComponent(settings);
    settings.number = 2;
    listenerComponent2 = listenerSystem->createComponent(settings);


    settings.sender = true;
    settings.number = 1;
    senderComponent1 = senderSystem->createComponent(settings);
    settings.number = 2;
    senderComponent2 = senderSystem->createComponent(settings);
}


void Test_EventManager::cleanUp() {
    delete(senderSystem);
    delete(listenerSystem);
}


Test_EventManager::Test_EventManager(TestLogger * const logger) : UnitTest(logger) {
    unit = "EventManager";
    testCaseCount = 7;
}
