/**
 * @file unittest.h
 */

#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>

class TestLogger;


/**
 * @class UnitTest
 * @brief Basisklasse für Unittests.
 */
class UnitTest
{
private:
    TestLogger * const logger;
protected:
    std::string unit = "UnitTest";
    int currentTestCase = 0;
    int testCaseCount = 0;
    void log(std::string text);
    void reportSuccess();
    void reportSuccess(std::string text);
    void reportFailure();
    void reportFailure(std::string text);
    virtual void startTests() = 0;
    virtual void init() = 0;
    virtual void cleanUp() = 0;
    //UnitTest() {}
public:
    void start();
    UnitTest(TestLogger * const logger);
};

#endif // UNITTEST_H
