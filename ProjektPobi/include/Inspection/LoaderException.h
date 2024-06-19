#ifndef FILELOADEXCEPTION_H
#define FILELOADEXCEPTION_H

#include <stdexcept>
#include <string>

class FileLoadException : public std::runtime_error {
public:
    explicit FileLoadException(const std::string& message)
        : std::runtime_error("File Load Error: " + message) {}
};

#endif // FILELOADEXCEPTION_H
