#include "Motorcycle.h"
#include "Inspection/InspectionStrategy.h"
#include "Inspection/InspectionException.h"

Motorcycle::Motorcycle(const std::string& reg_num, int year, int capacity, double brake_cond, double tire_cond, double frame_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy)
    : Vehicle(reg_num, year, brake_cond, tire_cond, expiry_date), frame_condition(frame_cond), inspection_strategy(strategy) {}

void Motorcycle::performInspection() const {
    inspection_strategy->inspect(*this);
}

int Motorcycle::getGarageSpace() const {
    return 1;
}

double Motorcycle::getFrameCondition() const {
    return frame_condition;
}

std::ostream& operator<<(std::ostream& os, const Motorcycle& motorcycle) {
    os << static_cast<const Vehicle&>(motorcycle) << ", Frame Condition: " << motorcycle.frame_condition;
    return os;
}
