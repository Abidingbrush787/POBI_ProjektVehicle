#include "Manager.h"
#include "Inspection/InspectionException.h"

Manager::Manager(Container<Vehicle>& garage, Container<Vehicle>& parking) : garage(garage), parking(parking) {}

void Manager::performInspections() {
    auto vehicles = garage.getItems();
    for (const auto& vehicle : vehicles) {
        try {
            vehicle->performInspection();
            std::cout << "Vehicle " << vehicle->getRegistrationNumber() << "+ passed inspection. " << std::endl;
        } catch (const InspectionException& e) {
            std::cout << "Vehicle " << vehicle->getRegistrationNumber() << "- failed inspection: " << e.what() << std::endl;
            parking.addItem(vehicle);
            garage.removeItem(vehicle);
        }
    }
}
