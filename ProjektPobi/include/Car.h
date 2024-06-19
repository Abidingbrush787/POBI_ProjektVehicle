#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <memory>

class InspectionStrategy;

class Car : public Vehicle {
private:
    int number_of_doors;
    double engine_condition; // Wskaźnik stanu silnika (0-100)
    std::shared_ptr<InspectionStrategy> inspection_strategy;

public:
    Car(const std::string& reg_num, int year, int doors, double brake_cond, double tire_cond, double engine_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy);
    void performInspection() const override;
    int getGarageSpace() const override;

    friend std::ostream& operator<<(std::ostream& os, const Car& car);

    double getEngineCondition() const;
};

#endif // CAR_H
