#include "Vehicle.h"

Vehicle::Vehicle(const std::string& reg_num, int year, double brake_cond, double tire_cond, const grDate& expiry_date)
    : registration_number(reg_num), year_of_production(year), brake_condition(brake_cond), tire_condition(tire_cond), inspection_expiry_date(expiry_date) {}

std::string Vehicle::getRegistrationNumber() const {
    return registration_number;
}

int Vehicle::getYearOfProduction() const {
    return year_of_production;
}

double Vehicle::getBrakeCondition() const {
    return brake_condition;
}

double Vehicle::getTireCondition() const {
    return tire_condition;
}

grDate Vehicle::getInspectionExpiryDate() const {
    return inspection_expiry_date;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    os << "Registration Number: " << vehicle.registration_number << ", Year: " << vehicle.year_of_production
       << ", Brake Condition: " << vehicle.brake_condition << ", Tire Condition: " << vehicle.tire_condition;
    return os;
}
