#include "testlogger.h"
//#include <cstdio>
#include <iostream>
#include <iomanip>


/**
 * @brief Prüft, ob der Unittest schon vorhanden ist und erstellt einen Eintrag, falls nicht.
 * @param unit Der Unitname
 */
void TestLogger::createEntryIfRequired(std::string unit) {
    if (!statistics.count(unit))
        statistics[unit] = UnitTestStatistics();
}


/**
 * @brief Gibt den Text formatiert mit Unit und Testcase an.
 * @param unit Der Unitname
 * @param testCase Der derzeitige Testcase
 * @param text Der auszugebende Text
 */
void TestLogger::log(std::string unit, int testCase, std::string text) {
    createEntryIfRequired(unit);

    std::cout << std::setw(23) << unit + " : " + std::to_string(testCase) + " : ";
    std::cout << text << std::endl;
}


/**
 * @brief Meldet einen erfolgreichen Test
 * @param unit Der Unitname
 * @param testCase Der derzeitige Testcase
 */
void TestLogger::reportSuccess(std::string unit, int testCase) {
    log(unit, testCase, "Success.");
    createEntryIfRequired(unit);
    statistics.at(unit).testsSucceeded += 1;
}


/**
 * @brief Meldet einen erfolgreichen Test mit Erfolgsmeldung
 * @param unit Der Unitname
 * @param testCase Der derzeitige Testcase
 * @param text Die Erfolgsmeldung
 */
void TestLogger::reportSuccess(std::string unit, int testCase, std::string text) {
    log(unit, testCase, "Success. " + text);
    createEntryIfRequired(unit);
    statistics.at(unit).testsSucceeded += 1;
}


/**
 * @brief Meldet einen gescheiterten Test
 * @param unit Der Unitname
 * @param testCase Der derzeitige Testcase
 */
void TestLogger::reportFailure(std::string unit, int testCase) {
    log(unit, testCase, "Failure.");
    createEntryIfRequired(unit);
    statistics.at(unit);
}

/**
 * @brief Meldet einen gescheiterten Test mit Fehlermeldung
 * @param unit Der Unitname
 * @param testCase Der derzeitige Testcase
 * @param text Die Fehlermeldung
 */
void TestLogger::reportFailure(std::string unit, int testCase, std::string text) {
    log(unit, testCase, "Failure. " + text);
    createEntryIfRequired(unit);
    statistics.at(unit);
}


/**
 * @brief Meldet eine Exception
 * @param unit Der Unitname
 * @param cause Der Grund der Exception
 */
void TestLogger::reportException(std::string unit, std::string cause) {
    createEntryIfRequired(unit);
    UnitTestStatistics & stat = statistics.at(unit);
    int testcase = stat.total() + 1;

    log(unit, testcase, "Exception occured. Cause: " + cause);
}


/**
 * @brief Gibt Statistiken über den Unittest aus.
 * @param unit Der Unitname
 * @param testCaseCount Die gesamte Anzahl an Testcases.
 *
 * Zählt zusätzlich gescheiterte Testcases hinzu, falls mehr testCaseCount
 * größer als die Anzahl bisher gezählter Testcases ist.
 */
void TestLogger::review(std::string unit, int testCaseCount) {
    createEntryIfRequired(unit);
    UnitTestStatistics & stat = statistics.at(unit);

    if (stat.total() > testCaseCount) {
        log(unit, 0, "Warning: Given TestCaseCount smaller than counted tests.");

    } else if (stat.total() < testCaseCount) {
        stat.testsFailed = testCaseCount - stat.testsSucceeded;
    }

    int succeededPercentage = (int) ( ((float) stat.testsSucceeded)
                                     / (stat.testsSucceeded + stat.testsFailed) * 100);

    int failedPercentage = (int) ( ((float) stat.testsFailed)
                                     / (stat.testsSucceeded + stat.testsFailed) * 100);

    std::string report = "Tests completed. Tests succeeded: " + std::to_string(stat.testsSucceeded)
                         + " (" + std::to_string(succeededPercentage) + "%). "
                         + "Tests Failed: " + std::to_string(stat.testsFailed)
                         + " (" + std::to_string(failedPercentage) + "%). ";
    log(unit, 0, report);
    std::cout << std::endl;
}


TestLogger::TestLogger() {

}
