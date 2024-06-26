#define BOOST_TEST_MODULE GarageTest
#include <boost/test/included/unit_test.hpp>
#include "Containers/Garage.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include "Inspection/CarInspectionStrategy.h"
#include "Inspection/TruckInspectionStrategy.h"
#include "Inspection/MotorcycleInspectionStrategy.h"
#include <boost/date_time/gregorian/gregorian.hpp>

BOOST_AUTO_TEST_CASE(AddAndRemoveVehicle) {
    Garage garage(10);
    boost::gregorian::date expiry_date(2025, 6, 15);
    auto car_strategy = std::make_shared<CarInspectionStrategy>();
    auto truck_strategy = std::make_shared<TruckInspectionStrategy>();
    auto motorcycle_strategy = std::make_shared<MotorcycleInspectionStrategy>();

    auto car = std::make_shared<Car>("ABC123", 2022, 4, 80.0, 85.0, 90.0, expiry_date, car_strategy);
    auto truck = std::make_shared<Truck>("DEF456", 2022, 20.0, 80.0, 85.0, 90.0, expiry_date, truck_strategy);
    auto motorcycle = std::make_shared<Motorcycle>("GHI789", 2022, 600, 80.0, 85.0, 90.0, expiry_date, motorcycle_strategy);

    BOOST_CHECK(garage.addItem(car));
    BOOST_CHECK(garage.addItem(truck));
    BOOST_CHECK(garage.addItem(motorcycle));

    BOOST_CHECK_EQUAL(garage.getItems().size(), 3);

    garage.removeItem(car);
    BOOST_CHECK_EQUAL(garage.getItems().size(), 2);

    garage.removeItem(truck);
    garage.removeItem(motorcycle);
    BOOST_CHECK_EQUAL(garage.getItems().size(), 0);
}
