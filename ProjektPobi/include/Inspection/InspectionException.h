#ifndef INSPECTIONEXCEPTION_H
#define INSPECTIONEXCEPTION_H

#include <exception>
#include <string>

class InspectionException : public std::exception {
public:
    explicit InspectionException(const std::string& message) : msg(message) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
private:
    std::string msg;
};

#endif // INSPECTIONEXCEPTION_H

