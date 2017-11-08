#include "test_fixedindexarray.h"
#include "utils/fixedindexarray.h"

/**
 * @brief Testet FixedIndexArray.add()
 */
void Test_FixedIndexArray::test1() {
    currentTestCase = 1;
    log("Testing: add() and getSize()");

    for (unsigned int i = 50; i < 150; i++) {
        fixArray1->add(i);
        fixArray2->add(i);
    }

    if (fixArray1->getSize() == 100 && fixArray2->getSize() == 100)
        reportSuccess();
    else
        reportFailure();
}

/**
 * @brief Testet FixedIndexArray.erase()
 */
void Test_FixedIndexArray::test2() {
    currentTestCase = 2;
    log("Testing: erase()");

    for (unsigned int i = 0; i < 500; i++) {
        fixArray1->add(i);
        fixArray2->add(i);
    }

    for (unsigned int i = 0; i < 250; i++) {
        fixArray1->erase(2*i);
        fixArray2->erase(2*i);
    }

    if (fixArray1->getSize() != 250 || fixArray2->getSize() != 250)
        reportFailure();

    for (unsigned int i = 0; i < 50; i++) {
        fixArray1->add(i);
        fixArray2->add(i);
    }

    if (fixArray1->getSize() == 300 || fixArray2->getSize() == 300)
        reportSuccess();
    else
        reportFailure();
}


/**
 * @brief Testet FixedIndexArray.get()
 */
void Test_FixedIndexArray::test3() {
    currentTestCase = 3;
    log("Testing: get()");


    for (unsigned int i = 100; i < 205; i++) {
        fixArray1->add(i);
        fixArray2->add(i);
    }

    for (unsigned int i = 0; i < 100; i++) {
        if (fixArray1->get(i) != i+100 || fixArray2->get(i) != i+100) {
            std::string message1 = "Error: Incorrect values received.";
            std::string message2 = "(Array1) Correct: " + std::to_string(i+100)
                                + " - Got: " + std::to_string(fixArray1->get(i));
            std::string message3 = "(Array2) Correct: " + std::to_string(i+100)
                                + " - Got: " + std::to_string(fixArray2->get(i));
            log(message1);
            log(message2);
            log(message3);
            reportFailure();
            return;
        }
    }

    for (unsigned int i = 0; i < 50; i++) {
        fixArray1->erase(2*i);
        fixArray2->erase(2*i);
    }

    for (unsigned int i = 0; i < 50; i++) {
        if (fixArray1->get(2*i+1) != 2*i+101 || fixArray2->get(2*i+1) != 2*i+101) {
            std::string message1 = "Error: Incorrect values received.";
            std::string message2 = "(Array1) Correct: " + std::to_string(2*i+101)
                                + " - Got: " + std::to_string(fixArray1->get(2*i+1));
            std::string message3 = "(Array2) Correct: " + std::to_string(2*i+101)
                                + " - Got: " + std::to_string(fixArray2->get(2*i+1));
            log(message1);
            log(message2);
            log(message3);
            reportFailure();
            return;
        }
    }

    reportSuccess();
}


/**
 * @brief Testet FixedIndexArray.getCapacity()
 */
void Test_FixedIndexArray::test4() {
    currentTestCase = 4;
    log("Testing: getCapacity()");
    if (fixArray1->getCapacity() != 100 || fixArray2->getCapacity() != 3) {
        reportFailure();
        return;
    }

    for (unsigned int i = 0; i < 100; i++) {
        fixArray1->add(i);
    }

    for (unsigned int i = 0; i < 3; i++) {
        fixArray2->add(i);
    }

    if (fixArray1->getCapacity() != 100 || fixArray2->getCapacity() != 3) {
        reportFailure();
        return;
    }

    for (unsigned int i = 0; i < 100; i++) {
        fixArray1->erase(i);
    }

    for (unsigned int i = 0; i < 3; i++) {
        fixArray2->erase(i);
    }

    for (unsigned int i = 0; i < 100; i++) {
        fixArray1->add(i);
    }

    for (unsigned int i = 0; i < 3; i++) {
        fixArray2->add(i);
    }

    if (fixArray1->getCapacity() != 100 || fixArray2->getCapacity() != 3) {
        reportFailure();
        return;
    }

    fixArray1->add(99);
    fixArray2->add(99);

    if (fixArray1->getCapacity() != 200 || fixArray2->getCapacity() != 6)
        reportFailure();
    else
        reportSuccess();
}


void Test_FixedIndexArray::startTests() {
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
}

void Test_FixedIndexArray::init() {
    fixArray1 = new FixedIndexArray();
    fixArray2 = new FixedIndexArray(3);
}


void Test_FixedIndexArray::cleanUp() {
    delete(fixArray1);
    delete(fixArray2);
}


Test_FixedIndexArray::Test_FixedIndexArray(TestLogger * const logger) : UnitTest(logger) {
    unit = "FixedIndexArray";
    testCaseCount = 4;
}
