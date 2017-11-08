/**
 * @file test_gamesystem.h
 */

#ifndef TEST_GAMESYSTEM_H
#define TEST_GAMESYSTEM_H

#include "tests/unittest.h"

class Helper_GameSystem_1;
class Handle;

/**
 * @class Test_GameSystem
 * @brief Unittest für GameSystem.
 *
 * Testet nicht die Eventsystem-Funktionalitäten.
 */
class Test_GameSystem : public UnitTest
{
private:
    Helper_GameSystem_1* system;
    //unsigned int* handles;
    Handle** handles;
    unsigned int length = 0;
    std::string arrayToString(int* array, unsigned int length);
    void test1();
protected:
    void startTests();
    void init();
    void cleanUp();
public:
    Test_GameSystem(TestLogger * const logger);
};

#endif // TEST_GAMESYSTEM_H
