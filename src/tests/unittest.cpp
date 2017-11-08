#include "unittest.h"
#include "testlogger.h"

void UnitTest::log(std::string text) {
    logger->log(unit, currentTestCase, text);
}

void UnitTest::reportSuccess() {
    logger->reportSuccess(unit, currentTestCase);
}


void UnitTest::reportSuccess(std::string text) {
    logger->reportSuccess(unit, currentTestCase, text);
}


void UnitTest::reportFailure() {
    logger->reportFailure(unit, currentTestCase);
}


void UnitTest::reportFailure(std::string text) {
    logger->reportFailure(unit, currentTestCase, text);
}


/**
 * @brief Startet die Unittests.
 */
void UnitTest::start() {
    log("Testing: " + unit);
    try {
        startTests();
    } catch (const std::exception& e) {
        //log("Exception occured in init. Cause: " + e.what());
        logger->reportException(unit, e.what());
    }
    logger->review(unit, testCaseCount);
}

UnitTest::UnitTest(TestLogger* const logger) : logger(logger){
}
