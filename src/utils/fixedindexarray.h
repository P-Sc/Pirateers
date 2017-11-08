/** @file fixedindexarray.h
 * @class FixedIndexArray
 * @brief Wrapper-Klasse für "unsigned int"-Arrays.
 *        Dabei haben Elemente einen unveränderlichen Index.
 */

#ifndef FIXLENGTHARRAY_H
#define FIXLENGTHARRAY_H

#include <list>


/**
 * @class FixedIndexArray
 * @brief Dynamisches Array mit "festen Plätzen"
 *
 * Einmal eingefügte Werte verändern nicht ihren Index.
 * Wird z.B. der Wert 27 an dem Index 5 eingefügt, behält das Array am Index 5
 * den Wert 27 bis diese Stelle mit erase() freigegeben wird, egal ob andere
 * Elemente eingefügt oder gelöscht werden.
 *
 * Das Array erhöht dynamisch seine Kapazität, verringert sie jedoch niemals.
 */
class FixedIndexArray
{
private:
    void appendStepSize();
    std::list<unsigned int> unusedPositions;
    unsigned int* array;
    bool* arrayUsage;
    unsigned int capacity = 0;
    unsigned int size = 0;
    unsigned int stepSize = 100;
    unsigned int maxElement = 0;
    bool initialized = false;

public:
    bool isUsed(unsigned int index);
    unsigned int add(unsigned int value);
    void erase(unsigned int index);
    unsigned int get(unsigned int index);
    unsigned int & operator[] (unsigned int index);
    unsigned int getSize();
    unsigned int getCapacity();
    //std::list<unsigned int> getUsedPositions();
    FixedIndexArray();
    FixedIndexArray(unsigned int stepSize);
    ~FixedIndexArray();
};

#endif // FIXLENGTHARRAY_H
