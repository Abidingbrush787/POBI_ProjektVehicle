#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include "Containers/Garage.h"
#include "Containers/Parking.h"
#include "Inspection/LoaderException.h"

class UserInterface {
public:
    UserInterface(Garage& garage, Parking& parking);

    void showMenu();
    void addVehicle();
    void listVehicles() const;
    void performInspections();
    void saveState(const std::string& filename) const;
    void loadState(const std::string& filename);
    void removeVehicle(const std::string& reg_num);

private:
    Garage& garage;
    Parking& parking;
};

#endif // USERINTERFACE_H
