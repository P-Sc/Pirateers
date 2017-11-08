/**
 * @file test_fixedindexarray.h
 */

#ifndef TEST_FIXEDINDEXARRAY_H
#define TEST_FIXEDINDEXARRAY_H

#include "tests/unittest.h"

class FixedIndexArray;

/**
 * @class Test_FixedIndexArray
 * @brief Unittest für FixedIndexArray
 */
class Test_FixedIndexArray : public UnitTest
{
private:
    FixedIndexArray * fixArray1;
    FixedIndexArray * fixArray2;

    void test1();
    void test2();
    void test3();
    void test4();
protected:
    void startTests();
    void init();
    void cleanUp();
public:
    Test_FixedIndexArray(TestLogger * const logger);
};

#endif // TEST_FIXEDINDEXARRAY_H
