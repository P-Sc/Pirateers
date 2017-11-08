#include "test_gamesystem.h"
#include "helper_gamesystem_1.h"
#include "helper_component_1.h"

typedef Helper_Settings_1 HSettings;

/**
 * @brief Konvertiert ein Integer-Array in einen String
 * @param array Das Array
 * @param length Die Länge des Arrays
 */
std::string Test_GameSystem::arrayToString(int* array, unsigned int length) {
    std::string text = "|";
    for (unsigned int i = 0; i < length; i++) {
        text += std::to_string(array[i]) + "|";
    }
    return text;
}

/**
 * @brief Testet createComponent(), eraseComponent(), getCount(), update()
 *
 * Testet, ob Komponenten richtig in das Array eingefügt, gelöscht und verschoben werden.
 */
void Test_GameSystem::test1() {
    currentTestCase = 1;
    log("Testing: createComponent(), eraseComponent(), getCount(), update()");
    HSettings settings;

    log ("Adding Components");
    for (unsigned int i = 0; i < length; i++) {
        settings.number = -i;
        handles[i] = system->createComponent(settings);
    }

    if (system->getCount() != length) {
        reportFailure();
        return;
    }

    log("Erasing Components");

    for (unsigned int i = 0; i < length/2; i++)
        delete handles[i*2];

    system->update(5.f);

    if (system->getCount() != length/2) {
        reportFailure();
        return;
    }

    int* componentNumbers = system->getComponentArray(length);

    // Stellen 0, 2, 4
    for (int i = 0; i < 5; i += 2) {
        if (componentNumbers[i] != (-10+1+i)) {
            reportFailure("Expected component mismatch");
            log("Array: " + arrayToString(componentNumbers, 10));
            return;
        }
    }

    // Stellen 1, 3
    if (componentNumbers[1] != -1 || componentNumbers[3] != -3) {
        reportFailure("Expected component mismatch");
        log("Array: " + arrayToString(componentNumbers, 10));
        return;
    }

    /* Stellen 5,6,7,8,9
     * Bei Fehlern weglassen, da ein möglicherweise freigegebener
     * Speicherbereich gelesen wird
     */
    for (int i = 5; i < 10; i++) {
        if (componentNumbers[i] != 1) {
            reportFailure("Expected component mismatch");
            log("Array: " + arrayToString(componentNumbers, 10));
            return;
        }
    }

    delete[] componentNumbers;

    for (unsigned int i = 0; i < length/2; i++)
        delete handles[i*2 + 1];

    reportSuccess();
}


void Test_GameSystem::startTests() {
    init();
    test1();
    cleanUp();
}


void Test_GameSystem::init() {
    system = new Helper_GameSystem_1();
    handles = new Handle*[10];
    length = 10;
}


void Test_GameSystem::cleanUp() {
    delete(system);
    delete[] handles;
    length = 0;
}


Test_GameSystem::Test_GameSystem(TestLogger* const logger) : UnitTest(logger) {
    unit = "GameSystem";
    testCaseCount = 1;
}
