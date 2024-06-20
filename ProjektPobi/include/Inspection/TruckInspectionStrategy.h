#ifndef TRUCKINSPECTIONSTRATEGY_H
#define TRUCKINSPECTIONSTRATEGY_H

#include "InspectionStrategy.h"
#include "InspectionException.h"
#include "Truck.h"

class TruckInspectionStrategy : public InspectionStrategy {
public:
    void inspect(const Vehicle& vehicle) const override {
        const Truck& truck = dynamic_cast<const Truck&>(vehicle);
        if (truck.getBrakeCondition() < 50) {
            throw InspectionException("Truck failed inspection due to poor brake condition.");
        }
        if (truck.getTireCondition() < 50) {
            throw InspectionException("Truck failed inspection due to poor tire condition.");
        }
        if (truck.getCargoCondition() < 50) {
            throw InspectionException("Truck failed inspection due to poor cargo condition.");
        }
        if (boost::gregorian::day_clock::local_day() > truck.getInspectionExpiryDate()) {
            throw InspectionException("Truck failed inspection due to expired inspection.");
        }
        std::cout << "Performing inspection on truck with registration number: "
                  << truck.getRegistrationNumber() << std::endl;
    }
};

#endif // TRUCKINSPECTIONSTRATEGY_H
