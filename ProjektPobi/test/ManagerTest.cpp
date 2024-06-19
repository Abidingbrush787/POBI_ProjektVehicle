#define BOOST_TEST_MODULE ManagerTest
#include <boost/test/included/unit_test.hpp>
#include "Manager.h"
#include "Containers/Garage.h"
#include "Containers/Parking.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include "Inspection/CarInspectionStrategy.h"
#include "Inspection/TruckInspectionStrategy.h"
#include "Inspection/MotorcycleInspectionStrategy.h"
#include <boost/date_time/gregorian/gregorian.hpp>

BOOST_AUTO_TEST_CASE(PerformInspections) {
    Garage garage(10);
    Parking parking(100);
    boost::gregorian::date expiry_date(2025, 6, 15);
    auto car_strategy = std::make_shared<CarInspectionStrategy>();
    auto truck_strategy = std::make_shared<TruckInspectionStrategy>();
    auto motorcycle_strategy = std::make_shared<MotorcycleInspectionStrategy>();

    auto car = std::make_shared<Car>("ABC123", 2022, 4, 80.0, 85.0, 90.0, expiry_date, car_strategy);
    auto truck = std::make_shared<Truck>("DEF456", 2022, 20.0, 80.0, 85.0, 90.0, expiry_date, truck_strategy);
    auto motorcycle = std::make_shared<Motorcycle>("GHI789", 2022, 600, 80.0, 85.0, 90.0, expiry_date, motorcycle_strategy);

    garage.addItem(car);
    garage.addItem(truck);
    garage.addItem(motorcycle);

    Manager manager(garage, parking);
    manager.performInspections();

    BOOST_CHECK_EQUAL(garage.getItems().size(), 3); // Wszystkie pojazdy powinny przejść inspekcję i pozostać w garażu

    auto faulty_car = std::make_shared<Car>("XYZ987", 1990, 4, 20.0, 25.0, 30.0, expiry_date, car_strategy);
    garage.addItem(faulty_car);
    manager.performInspections();

    BOOST_CHECK_EQUAL(garage.getItems().size(), 3); // Wadliwy samochód powinien zostać usunięty z garażu
    BOOST_CHECK_EQUAL(parking.getItems().size(), 1); // Wadliwy samochód powinien być na parkingu
}
