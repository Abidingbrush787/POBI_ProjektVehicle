#ifndef MOTORCYCLEINSPECTIONSTRATEGY_H
#define MOTORCYCLEINSPECTIONSTRATEGY_H

#include "InspectionStrategy.h"
#include "InspectionException.h"
#include "Motorcycle.h"

// Strategia inspekcji dla motocykli
class MotorcycleInspectionStrategy : public InspectionStrategy {
public:
    void inspect(const Vehicle& vehicle) const override {
        const Motorcycle& motorcycle = dynamic_cast<const Motorcycle&>(vehicle);
        if (motorcycle.getBrakeCondition() < 50 || motorcycle.getTireCondition() < 50 || motorcycle.getFrameCondition() < 50 || boost::gregorian::day_clock::local_day() > motorcycle.getInspectionExpiryDate()) {
            throw InspectionException("Motorcycle failed inspection due to poor condition or expired inspection.");
        }
        std::cout << "Performing inspection on motorcycle with registration number: "
                  << motorcycle.getRegistrationNumber() << std::endl;
    }
};

#endif // MOTORCYCLEINSPECTIONSTRATEGY_H
