#ifndef CARINSPECTIONSTRATEGY_H
#define CARINSPECTIONSTRATEGY_H

#include "InspectionStrategy.h"
#include "InspectionException.h"
#include "Car.h"

class CarInspectionStrategy : public InspectionStrategy {
public:
    void inspect(const Vehicle& vehicle) const override {
        const Car& car = dynamic_cast<const Car&>(vehicle);
        if (car.getYearOfProduction() < 2000) {
            throw InspectionException("Car is too old for inspection.");
        }
        if (car.getBrakeCondition() < 50 || car.getTireCondition() < 50 || car.getEngineCondition() < 50 || boost::gregorian::day_clock::local_day() > car.getInspectionExpiryDate()) {
            throw InspectionException("Car failed inspection due to poor condition or expired inspection.");
        }
        std::cout << "Performing inspection on car with registration number: "
                  << car.getRegistrationNumber() << std::endl;
    }
};

#endif // CARINSPECTIONSTRATEGY_H
