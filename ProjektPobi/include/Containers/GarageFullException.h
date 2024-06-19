#ifndef GARAGEFULLEXCEPTION_H
#define GARAGEFULLEXCEPTION_H

#include <stdexcept>
#include <string>

class GarageFullException : public std::runtime_error {
public:
    explicit GarageFullException(const std::string& message)
        : std::runtime_error("Garage Full Error: " + message) {}
};

#endif // GARAGEFULLEXCEPTION_H
