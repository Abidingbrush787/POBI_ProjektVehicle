#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"
#include <memory>

class InspectionStrategy;

class Truck : public Vehicle {
private:
    double cargo_condition; // Stan ładunku (0-100)
    std::shared_ptr<InspectionStrategy> inspection_strategy; // Strategia inspekcji

public:
    Truck(const std::string& reg_num, int year, double capacity, double brake_cond, double tire_cond, double cargo_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy);

    // Implementacja metod wirtualnych
    void performInspection() const override;
    int getGarageSpace() const override;

    // Getter stanu ładunku
    double getCargoCondition() const;

    // Operator wyjścia
    friend std::ostream& operator<<(std::ostream& os, const Truck& truck);
};

#endif // TRUCK_H
