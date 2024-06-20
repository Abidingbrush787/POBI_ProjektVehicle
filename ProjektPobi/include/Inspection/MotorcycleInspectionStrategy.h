#ifndef MOTORCYCLEINSPECTIONSTRATEGY_H
#define MOTORCYCLEINSPECTIONSTRATEGY_H

#include "InspectionStrategy.h"
#include "InspectionException.h"
#include "Motorcycle.h"

class MotorcycleInspectionStrategy : public InspectionStrategy {
public:
    void inspect(const Vehicle& vehicle) const override {
        const Motorcycle& motorcycle = dynamic_cast<const Motorcycle&>(vehicle);
        if (motorcycle.getBrakeCondition() < 50) {
            throw InspectionException("Motorcycle failed inspection due to poor brake condition.");
        }
        if (motorcycle.getTireCondition() < 50) {
            throw InspectionException("Motorcycle failed inspection due to poor tire condition.");
        }
        if (motorcycle.getFrameCondition() < 50) {
            throw InspectionException("Motorcycle failed inspection due to poor frame condition.");
        }
        if (boost::gregorian::day_clock::local_day() > motorcycle.getInspectionExpiryDate()) {
            throw InspectionException("Motorcycle failed inspection due to expired inspection.");
        }
        std::cout << "Performing inspection on motorcycle with registration number: "
                  << motorcycle.getRegistrationNumber() << std::endl;
    }
};

#endif // MOTORCYCLEINSPECTIONSTRATEGY_H
