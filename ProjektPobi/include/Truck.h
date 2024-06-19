#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"
#include <memory>

class InspectionStrategy;

class Truck : public Vehicle {
private:
    double cargo_condition; // Wskaźnik stanu ładunku (0-100)
    std::shared_ptr<InspectionStrategy> inspection_strategy;

public:
    Truck(const std::string& reg_num, int year, double capacity, double brake_cond, double tire_cond, double cargo_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy);
    void performInspection() const override;
    int getGarageSpace() const override;

    friend std::ostream& operator<<(std::ostream& os, const Truck& truck);

    double getCargoCondition() const;
};

#endif // TRUCK_H
