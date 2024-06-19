#ifndef MANAGER_H
#define MANAGER_H

#include "Containers/Container.h"
#include "Vehicle.h"

class Manager {
private:
    Container<Vehicle>& garage;
    Container<Vehicle>& parking;

public:
    Manager(Container<Vehicle>& garage, Container<Vehicle>& parking);
    void performInspections();
};

#endif // MANAGER_H
