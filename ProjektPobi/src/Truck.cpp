#include "Truck.h"
#include "Inspection/InspectionStrategy.h"
#include "Inspection/InspectionException.h"

Truck::Truck(const std::string& reg_num, int year, double capacity, double brake_cond, double tire_cond, double cargo_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy)
    : Vehicle(reg_num, year, brake_cond, tire_cond, expiry_date), cargo_condition(cargo_cond), inspection_strategy(strategy) {}

void Truck::performInspection() const {
    inspection_strategy->inspect(*this);
}

int Truck::getGarageSpace() const {
    return 6;
}

double Truck::getCargoCondition() const {
    return cargo_condition;
}

std::ostream& operator<<(std::ostream& os, const Truck& truck) {
    os << static_cast<const Vehicle&>(truck) << ", Cargo Condition: " << truck.cargo_condition;
    return os;
}
