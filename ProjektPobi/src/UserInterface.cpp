#include "UserInterface.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include "Inspection/CarInspectionStrategy.h"
#include "Inspection/TruckInspectionStrategy.h"
#include "Inspection/MotorcycleInspectionStrategy.h"
#include "Containers/GarageFullException.h"
#include "Inspection/LoaderException.h"
#include "Manager.h" // Dodaj ten include
#include <fstream>
#include <iostream>

UserInterface::UserInterface(Garage& garage, Parking& parking) : garage(garage), parking(parking) {}

void UserInterface::showMenu() {
    int choice;
    do {
        std::cout << "1. Add Vehicle\n2. List Vehicles\n3. Perform Inspections\n4. Save State\n5. Load State\n6. Exit\n";
        std::cin >> choice;
        switch (choice) {
            case 1: addVehicle(); break;
            case 2: listVehicles(); break;
            case 3: performInspections(); break;
            case 4: {
                std::string filename;
                std::cout << "Enter filename to save state: ";
                std::cin >> filename;
                saveState(filename);
                break;
            }
            case 5: {
                std::string filename;
                std::cout << "Enter filename to load state: ";
                std::cin >> filename;
                try {
                    loadState(filename);
                } catch (const FileLoadException& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            }
            case 6: break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

void UserInterface::addVehicle() {
    int type;
    std::cout << "Select type of vehicle to add: 1. Car 2. Truck 3. Motorcycle\n";
    std::cin >> type;

    std::string reg_num;
    int year;
    double brake_cond, tire_cond, extra_cond;
    boost::gregorian::date expiry_date;
    std::cout << "Enter registration number: ";
    std::cin >> reg_num;
    std::cout << "Enter year of production: ";
    std::cin >> year;
    std::cout << "Enter brake condition (0-100): ";
    std::cin >> brake_cond;
    std::cout << "Enter tire condition (0-100): ";
    std::cin >> tire_cond;
    std::cout << "Enter inspection expiry date (YYYY-MM-DD): ";
    std::string date_str;
    std::cin >> date_str;
    expiry_date = boost::gregorian::from_simple_string(date_str);

    std::shared_ptr<Vehicle> vehicle;

    switch (type) {
        case 1: {
            int doors;
            std::cout << "Enter number of doors: ";
            std::cin >> doors;
            std::cout << "Enter engine condition (0-100): ";
            std::cin >> extra_cond;
            auto strategy = std::make_shared<CarInspectionStrategy>();
            vehicle = std::make_shared<Car>(reg_num, year, doors, brake_cond, tire_cond, extra_cond, expiry_date, strategy);
            break;
        }
        case 2: {
            std::cout << "Enter cargo condition (0-100): ";
            std::cin >> extra_cond;
            auto strategy = std::make_shared<TruckInspectionStrategy>();
            vehicle = std::make_shared<Truck>(reg_num, year, 15.5, brake_cond, tire_cond, extra_cond, expiry_date, strategy);
            break;
        }
        case 3: {
            std::cout << "Enter frame condition (0-100): ";
            std::cin >> extra_cond;
            auto strategy = std::make_shared<MotorcycleInspectionStrategy>();
            vehicle = std::make_shared<Motorcycle>(reg_num, year, 1, brake_cond, tire_cond, extra_cond, expiry_date, strategy);
            break;
        }
        default:
            std::cout << "Invalid type.\n";
            return;
    }

    try {
        if (garage.addItem(vehicle)) {
            std::cout << "Vehicle added to garage.\n";
        } else {
            throw GarageFullException("Garage is full. Cannot add vehicle.");
        }
    } catch (const GarageFullException& e) {
        std::cout << "Garage is full. Cannot add vehicle.\n";
    }
}

void UserInterface::listVehicles() const {
    std::cout << "Vehicles in garage:\n";
    garage.listItems();
    std::cout << "Vehicles in parking:\n";
    parking.listItems();
}

void UserInterface::performInspections() {
    Manager manager(garage, parking);
    manager.performInspections();
}

void UserInterface::saveState(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        const auto& vehicles = garage.getItems();
        for (const auto& vehicle : vehicles) {
            file << vehicle->getRegistrationNumber() << " "
                 << vehicle->getYearOfProduction() << " "
                 << vehicle->getBrakeCondition() << " "
                 << vehicle->getTireCondition() << " "
                 << boost::gregorian::to_simple_string(vehicle->getInspectionExpiryDate()) << "\n";
        }
        file.close();
        std::cout << "State saved to " << filename << ".\n";
    } else {
        std::cerr << "Unable to open file for saving.\n";
    }
}

void UserInterface::loadState(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        garage.clear();
        std::string reg_num;
        int year;
        double brake_cond, tire_cond, extra_cond;
        std::string date_str;
        boost::gregorian::date expiry_date;

        while (file >> reg_num >> year >> brake_cond >> tire_cond >> date_str) {
            expiry_date = boost::gregorian::from_simple_string(date_str);
            // Here you should also read specific vehicle data like doors for cars, cargo condition for trucks, etc.
            // For simplicity, we'll assume all loaded vehicles are cars.
            auto strategy = std::make_shared<CarInspectionStrategy>();
            auto vehicle = std::make_shared<Car>(reg_num, year, 4, brake_cond, tire_cond, 80, expiry_date, strategy); // Assuming default values for the remaining parameters
            garage.addItem(vehicle);
        }
        file.close();
        std::cout << "State loaded from " << filename << ".\n";
    } else {
        throw FileLoadException("Unable to open file: " + filename);
    }
}
