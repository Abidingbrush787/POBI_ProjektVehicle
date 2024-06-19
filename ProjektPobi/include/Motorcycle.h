#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"
#include <memory>

class InspectionStrategy;

class Motorcycle : public Vehicle {
private:
    double frame_condition; // Wskaźnik stanu ramy (0-100)
    std::shared_ptr<InspectionStrategy> inspection_strategy;

public:
    Motorcycle(const std::string& reg_num, int year, int capacity, double brake_cond, double tire_cond, double frame_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy);
    void performInspection() const override;
    int getGarageSpace() const override;

    friend std::ostream& operator<<(std::ostream& os, const Motorcycle& motorcycle);

    double getFrameCondition() const;
};

#endif // MOTORCYCLE_H
