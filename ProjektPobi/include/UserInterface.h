#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Containers/Container.h"
#include "Vehicle.h"
#include "Containers/Garage.h"
#include "Containers/Parking.h"

class UserInterface {
private:
    Garage& garage;
    Parking& parking;

public:
    UserInterface(Garage& garage, Parking& parking);

    void showMenu();
    void addVehicle();
    void listVehicles() const;
    void performInspections();
    void saveState(const std::string& filename) const;
    void loadState(const std::string& filename);
};

#endif // USERINTERFACE_H
