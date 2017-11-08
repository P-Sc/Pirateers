#include "fixedindexarray.h"
#include <stdexcept>
#include <cassert>

using std::list;

/**
 * @brief Vergrößert das Array um stepSize (Standard: 100)
 */
void FixedIndexArray::appendStepSize() {
    // unusedPosition anpassen
    for (unsigned int i = 0; i < stepSize; i++) {
        unusedPositions.push_back(i + capacity);
    }

    // Array anpassen
    unsigned int* newArray = new unsigned int[capacity + stepSize];
    bool* newArrayUsage = new bool[capacity + stepSize];

    if (initialized) {
        for (unsigned int i = 0; i < capacity; i++) {
            newArray[i] = array[i];
            newArrayUsage[i] = arrayUsage[i];
        }

        for (unsigned int i = capacity; i < capacity + stepSize; i++) {
            newArray[i] = 0;
            newArrayUsage[i] = false;
        }

        delete[] array;
        delete[] arrayUsage;
        array = newArray;
        arrayUsage = newArrayUsage;
    } else {
        array = newArray;
        arrayUsage = newArrayUsage;
        initialized = true;
    }

    capacity += stepSize;
}


bool FixedIndexArray::isUsed(unsigned int index) {
    return (index < capacity && arrayUsage[index] == true);
}


/**
 * @brief Fügt ein neues Element zum Array hinzu.
 *         Vergrößert das Array, falls nötig.
 *
 * @param value Wert des Elements
 * @return Index des Elements
 *
 */
unsigned int FixedIndexArray::add(unsigned int value) {
    if (size == capacity) {
        appendStepSize();
    } else if (size > capacity) {
        throw std::out_of_range("Impossible");
    }

    unsigned int index = unusedPositions.front();
    array[index] = value;
    arrayUsage[index] = true;
    unusedPositions.pop_front();
    size += 1;
    return index;
}


/**
 * @brief Entfernt ein Element. Verkleinert nicht das Array.
 *
 * @param index Der Index des zu entfernenden Elements
 */
void FixedIndexArray::erase(unsigned int index) {
    if ((index + 1) > capacity)
        throw std::out_of_range("Index is out of range. Index: " + std::to_string(index)
                                + " , Capacity: " + std::to_string(capacity));

    array[index] = 0;
    assert (arrayUsage[index] == true);
    arrayUsage[index] = false;
    size -= 1;
    // WTF
    /*
    typename list<unsigned int>::iterator it = unusedPositions.begin();
    typename list<unsigned int>::iterator end = unusedPositions.end();

    for (typename list<unsigned int>::iterator it = unusedPositions.begin();
            it != end; it++) {

        assert(index != *it);

        if (index < *it) {
            unusedPositions.erase(it);
            return;
        }
    }*/

    unusedPositions.push_back(index);
}

/**
 * @brief Gibt das Element an der Stelle index zurück.
 *
 * @param index Der index für das gewünschte Element
 * @return Das gewünschte Element
 */
unsigned int FixedIndexArray::get(unsigned int index) {
    if ((index + 1) > capacity)
        throw std::out_of_range("Index is out of range. Index: " + std::to_string(index)
                                + " , Capacity: " + std::to_string(capacity));
    else if (arrayUsage[index] == false) {
        throw std::out_of_range("Id unused");
    }

    return array[index];
}


/**
 * @brief Gibt eine Referenz des Elements an der Stelle index zurück.
 *
 * @param index Der index für das gewünschte Element
 * @return Das gewünschte Element
 */
unsigned int & FixedIndexArray::operator[] (unsigned int index) {
    if ((index + 1) > capacity)
        throw std::out_of_range("Index is out of range. Index: " + std::to_string(index)
                                + " , Capacity: " + std::to_string(capacity));
    else if (arrayUsage[index] == false) {
        throw std::out_of_range("Id unused");
    }

    return array[index];
}

/**
 * @brief Gibt die Anzahl der (benutzten) Elemente zurück.
 *
 * @return Anzahl der benutzten Elemente
 */
unsigned int FixedIndexArray::getSize() {
    return size;
}

/**
 * @brief Gibt die Kapazität zurück.
 *
 * @return Mögliche Kapazität
 */
unsigned int FixedIndexArray::getCapacity() {
    return capacity;
}



/*
 * @brief Gibt eine Liste der benutzten IDs zurück
 * @return Liste der benutzten IDs
 */
/*
std::list<unsigned int> FixedIndexArray::getUsedPositions() {
    std::list<unsigned int> usedPositions;
    unusedPositions.sort();
    std::list<unsigned int>::iterator it = unusedPositions.begin();
    for (unsigned int i = 0; i < capacity; i++) {
        if (it != unusedPositions.end() && (*it) == i)
            it++;
        else
            usedPositions.push_back(i);
    }
} */


/**
 * @brief Konstruktor. Übernimmt Standard-stepSize.
 */
FixedIndexArray::FixedIndexArray() {
    appendStepSize();
}


/**
 * @brief Konstruktor. Setzt neue stepSize
 * @param stepSize Die neue Schrittlänge für das erhöhen der Kapazität
 */
FixedIndexArray::FixedIndexArray(unsigned int stepSize) {
    if (stepSize > 0) {
        this->stepSize = stepSize;
    }

    appendStepSize();
}


FixedIndexArray::~FixedIndexArray() {
    delete[] array;
    delete[] arrayUsage;
}
