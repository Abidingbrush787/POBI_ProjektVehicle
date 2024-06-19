#ifndef INSPECTIONSTRATEGY_H
#define INSPECTIONSTRATEGY_H

// Klasa abstrakcyjna dla strategii inspekcji
class Vehicle;

class InspectionStrategy {
public:
    virtual void inspect(const Vehicle& vehicle) const = 0;
    virtual ~InspectionStrategy() = default;
};

#endif // INSPECTIONSTRATEGY_H
