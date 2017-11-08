#include "completetest.h"
#include "tests/testlogger.h"
#include "tests/test_fixedindexarray.h"
#include "tests/test_gamesystem.h"
#include "tests/test_eventmanager.h"
/**
 * @brief Startet alle Tests
 */
void CompleteTest::start() {
    TestLogger logger;

    Test_FixedIndexArray test1(&logger);
    test1.start();

    Test_GameSystem test2(&logger);
    test2.start();

    Test_EventManager test3(&logger);
    test3.start();
}

CompleteTest::CompleteTest()
{

}
