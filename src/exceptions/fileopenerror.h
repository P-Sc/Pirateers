/**
 * @file fileopenerror.h
 */

#ifndef FILEOPENERROR_H
#define FILEOPENERROR_H

class FileOpenError : public std::runtime_error {
public:
    FileOpenError(const char* cause) : std::runtime_error(cause) {}
};

#endif // FILEOPENERROR_H
