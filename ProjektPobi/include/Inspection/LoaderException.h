#ifndef FILELOADEXCEPTION_H
#define FILELOADEXCEPTION_H

#include <stdexcept>
#include <string>

// Wyjątek rzucany podczas błędu ładowania pliku
class FileLoadException : public std::runtime_error {
public:
    explicit FileLoadException(const std::string& message)
        : std::runtime_error("File Load Error: " + message) {}
};

#endif // FILELOADEXCEPTION_H
