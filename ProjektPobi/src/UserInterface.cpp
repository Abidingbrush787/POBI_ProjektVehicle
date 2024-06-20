#include "UserInterface.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include "Inspection/CarInspectionStrategy.h"
#include "Inspection/TruckInspectionStrategy.h"
#include "Inspection/MotorcycleInspectionStrategy.h"
#include "Containers/GarageFullException.h"
#include "Inspection/LoaderException.h"
#include "Manager.h"
#include "Containers/Month_controler.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::string dateToString(const boost::gregorian::date& date) {
    int year = date.year();
    int month = date.month();
    int day = date.day();
    std::stringstream ss;
    ss << year << "-" << monthToString(month) << "-" << day;
    return ss.str();
}

boost::gregorian::date stringToDate(const std::string& dateStr) {
    std::stringstream ss(dateStr);
    std::string yearStr, monthStr, dayStr;
    std::getline(ss, yearStr, '-');
    std::getline(ss, monthStr, '-');
    std::getline(ss, dayStr);

    int year = std::stoi(yearStr);
    int month = stringToMonth(monthStr);
    int day = std::stoi(dayStr);

    return grDate(year, month, day);
}

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
    std::cout << "----- Vehicles in garage (V) -----\n";
    garage.listItems();
    std::cout << "----- Vehicles in parking (X) -----\n";
    parking.listItems();
}

void UserInterface::performInspections() {
    Manager manager(garage, parking);
    manager.performInspections();
}

void UserInterface::saveState(const std::string& filename) const {
    fs::create_directory("Pojazdy_data");
    std::string filePath = "Pojazdy_data/" + filename;

    std::ofstream file(filePath);
    if (file.is_open()) {
        const auto& vehicles = parking.getItems();
        for (const auto& vehicle : vehicles) {
            if (dynamic_cast<Car*>(vehicle.get())) {
                file << "Car ";
            } else if (dynamic_cast<Truck*>(vehicle.get())) {
                file << "Truck ";
            } else if (dynamic_cast<Motorcycle*>(vehicle.get())) {
                file << "Motorcycle ";
            }

            file << vehicle->getRegistrationNumber() << " "
                 << vehicle->getYearOfProduction() << " "
                 << vehicle->getBrakeCondition() << " "
                 << vehicle->getTireCondition() << " "
                 << dateToString(vehicle->getInspectionExpiryDate());

            if (auto car = dynamic_cast<Car*>(vehicle.get())) {
                file << " " << car->getGarageSpace() << " " << car->getEngineCondition();
            } else if (auto truck = dynamic_cast<Truck*>(vehicle.get())) {
                file << " " << truck->getCargoCondition();
            } else if (auto motorcycle = dynamic_cast<Motorcycle*>(vehicle.get())) {
                file << " " << motorcycle->getFrameCondition();
            }

            file << "\n";
        }
        file.close();
        std::cout << "State saved to " << filePath << ".\n";
        std::cout << "File saved at: " << filePath << std::endl;
    } else {
        std::cerr << "Unable to open file for saving.\n";
    }
}

void UserInterface::loadState(const std::string& filename) {
    std::string filePath = "Pojazdy_data/" + filename;
    std::ifstream file(filePath);
    if (file.is_open()) {
        garage.clear();
        std::string reg_num, type;
        int year;
        double brake_cond, tire_cond, extra_cond1, extra_cond2;
        std::string date_str;
        grDate expiry_date;

        while (file >> type >> reg_num >> year >> brake_cond >> tire_cond >> date_str) {
            try {
                expiry_date = stringToDate(date_str);
            } catch (const std::exception& e) {
                std::cerr << "Invalid date format for vehicle " << reg_num << ": " << date_str << std::endl;
                continue;
            }

            if (type == "Car") {
                int doors;
                double engine_cond;
                if (!(file >> doors >> engine_cond)) {
                    std::cerr << "Invalid data for Car " << reg_num << std::endl;
                    continue;
                }
                auto strategy = std::make_shared<CarInspectionStrategy>();
                auto vehicle = std::make_shared<Car>(reg_num, year, doors, brake_cond, tire_cond, engine_cond, expiry_date, strategy);
                garage.addItem(vehicle);
            } else if (type == "Truck") {
                double cargo_cond;
                if (!(file >> cargo_cond)) {
                    std::cerr << "Invalid data for Truck " << reg_num << std::endl;
                    continue;
                }
                auto strategy = std::make_shared<TruckInspectionStrategy>();
                auto vehicle = std::make_shared<Truck>(reg_num, year, 15.5, brake_cond, tire_cond, cargo_cond, expiry_date, strategy); // Assuming default value for capacity
                garage.addItem(vehicle);
            } else if (type == "Motorcycle") {
                double frame_cond;
                if (!(file >> frame_cond)) {
                    std::cerr << "Invalid data for Motorcycle " << reg_num << std::endl;
                    continue;
                }
                auto strategy = std::make_shared<MotorcycleInspectionStrategy>();
                auto vehicle = std::make_shared<Motorcycle>(reg_num, year, 1, brake_cond, tire_cond, frame_cond, expiry_date, strategy); // Assuming default value for capacity
                garage.addItem(vehicle);
            } else {
                std::cerr << "Unknown vehicle type in file for " << reg_num << std::endl;
                continue;
            }
        }
        file.close();
        std::cout << "State loaded from " << filePath << ".\n";
    } else {
        throw FileLoadException("Unable to open file: " + filePath);
    }
}

