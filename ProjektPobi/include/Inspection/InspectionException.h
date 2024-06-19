#ifndef INSPECTIONEXCEPTION_H
#define INSPECTIONEXCEPTION_H

#include <stdexcept>
#include <string>

// Wyjątek rzucany podczas inspekcji
class InspectionException : public std::runtime_error {
public:
    explicit InspectionException(const std::string& message)
        : std::runtime_error("Inspection Error: " + message) {}
};

#endif // INSPECTIONEXCEPTION_H
