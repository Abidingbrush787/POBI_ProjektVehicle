#include "Car.h"
#include "Inspection/InspectionStrategy.h"
#include "Inspection/InspectionException.h"

Car::Car(const std::string& reg_num, int year, int doors, double brake_cond, double tire_cond, double engine_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy)
    : Vehicle(reg_num, year, brake_cond, tire_cond, expiry_date), number_of_doors(doors), engine_condition(engine_cond), inspection_strategy(strategy) {}

void Car::performInspection() const {
    inspection_strategy->inspect(*this);
}

int Car::getGarageSpace() const {
    return number_of_doors <= 4 ? 2 : 3;
}

double Car::getEngineCondition() const {
    return engine_condition;
}

std::ostream& operator<<(std::ostream& os, const Car& car) {
    os << static_cast<const Vehicle&>(car) << ", Doors: " << car.number_of_doors
       << ", Engine Condition: " << car.engine_condition;
    return os;
}
