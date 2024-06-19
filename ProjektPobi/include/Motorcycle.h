#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"
#include <memory>

class InspectionStrategy;

class Motorcycle : public Vehicle {
private:
    double frame_condition; // Stan ramy (0-100)
    std::shared_ptr<InspectionStrategy> inspection_strategy; // Strategia inspekcji

public:
    Motorcycle(const std::string& reg_num, int year, int capacity, double brake_cond, double tire_cond, double frame_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy);

    // Implementacja metod wirtualnych
    void performInspection() const override;
    int getGarageSpace() const override;

    // Getter stanu ramy
    double getFrameCondition() const;

    // Operator wyjścia
    friend std::ostream& operator<<(std::ostream& os, const Motorcycle& motorcycle);
};

#endif // MOTORCYCLE_H
