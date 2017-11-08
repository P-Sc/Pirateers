/**
 * @file test_eventManager.h
 */

#ifndef TEST_EVENTMANAGER_H
#define TEST_EVENTMANAGER_H

#include "tests/unittest.h"

class Helper_GameSystem_1;
class Handle;

/**
 * @class Test_EventManager
 * @brief Unittest für den EventManager und das komplette Event- und Nachrichtensysten,
 */
class Test_EventManager : public UnitTest
{
private:
    Helper_GameSystem_1 * listenerSystem;
    Helper_GameSystem_1 * senderSystem;
    Handle * senderComponent1;
    Handle * senderComponent2;
    Handle * listenerComponent1;
    Handle * listenerComponent2;

    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();
protected:
    void startTests();
    void init();
    void cleanUp();
public:
    Test_EventManager(TestLogger * const logger);
};

#endif // TEST_EVENTMANAGER_H
