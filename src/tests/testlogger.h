/**
 * @file testlogger.h
 */

#ifndef TESTLOGGER_H
#define TESTLOGGER_H

#include <string>
#include <map>


struct UnitTestStatistics {
    int testsSucceeded = 0;
    int testsFailed = 0;

    int total() {
        return testsSucceeded + testsFailed;
    }
};

/**
 * @class TestLogger
 * @brief Logger für Unittests
 *
 * Bietet eine formatierte Ausgabe und Statistiken für Unittests.
 */
class TestLogger
{
private:
    std::map<std::string, UnitTestStatistics> statistics;

    void createEntryIfRequired(std::string unit);
public:
    void log(std::string unit, int testCase, std::string text);
    void reportSuccess(std::string unit, int testCase);
    void reportSuccess(std::string unit, int testCase, std::string text);
    void reportFailure(std::string unit, int testCase);
    void reportFailure(std::string unit, int testCase, std::string text);
    void reportException(std::string unit, std::string cause);
    void review(std::string unit, int testCaseCount);

    TestLogger();
};

#endif // TESTLOGGER_H
