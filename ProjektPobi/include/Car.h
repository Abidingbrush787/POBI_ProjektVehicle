#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <memory>

class InspectionStrategy;

class Car : public Vehicle {
private:
    int number_of_doors; // Liczba drzwi
    double engine_condition; // Stan silnika (0-100)
    std::shared_ptr<InspectionStrategy> inspection_strategy; // Strategia inspekcji

public:
    Car(const std::string& reg_num, int year, int doors, double brake_cond, double tire_cond, double engine_cond, const boost::gregorian::date& expiry_date, std::shared_ptr<InspectionStrategy> strategy);

    // Implementacja metod wirtualnych
    void performInspection() const override;
    int getGarageSpace() const override;

    // Getter stanu silnika
    double getEngineCondition() const;

    // Operator wyjścia
    friend std::ostream& operator<<(std::ostream& os, const Car& car);
};

#endif // CAR_H
