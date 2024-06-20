#define BOOST_TEST_MODULE TruckTest
#include <boost/test/unit_test.hpp>
#include "Truck.h"
#include "Inspection/TruckInspectionStrategy.h"
#include "Inspection/InspectionException.h"
#include <boost/date_time/gregorian/gregorian.hpp>

BOOST_AUTO_TEST_CASE(TruckCreationTest) {
    boost::gregorian::date expiry_date(2025, 12, 31);
    auto strategy = std::make_shared<TruckInspectionStrategy>();
    Truck* truck = new Truck("DEF456", 2020, 20, 85, 90, 80, expiry_date, strategy);

    BOOST_CHECK_EQUAL(truck->getRegistrationNumber(), "DEF456");
    BOOST_CHECK_EQUAL(truck->getYearOfProduction(), 2020);
    BOOST_CHECK_EQUAL(truck->getBrakeCondition(), 85);
    BOOST_CHECK_EQUAL(truck->getTireCondition(), 90);
    BOOST_CHECK_EQUAL(truck->getCargoCondition(), 80);
    BOOST_CHECK_EQUAL(truck->getGarageSpace(), 6);

    delete truck; // Pamiętaj o zwolnieniu pamięci
}

BOOST_AUTO_TEST_CASE(TruckInspectionTest) {
    boost::gregorian::date expiry_date(2025, 12, 31);
    auto strategy = std::make_shared<TruckInspectionStrategy>();
    Truck* truck = new Truck("DEF456", 2020, 20, 85, 90, 80, expiry_date, strategy);

    BOOST_CHECK_NO_THROW(truck->performInspection());

    Truck* bad_brake_truck = new Truck("BADBRAKE", 2020, 20, 45, 90, 80, expiry_date, strategy);
    BOOST_CHECK_THROW(bad_brake_truck->performInspection(), InspectionException);

    Truck* bad_tire_truck = new Truck("BADTIRE", 2020, 20, 85, 45, 80, expiry_date, strategy);
    BOOST_CHECK_THROW(bad_tire_truck->performInspection(), InspectionException);

    Truck* bad_cargo_truck = new Truck("BADCARGO", 2020, 20, 85, 90, 45, expiry_date, strategy);
    BOOST_CHECK_THROW(bad_cargo_truck->performInspection(), InspectionException);

    Truck* expired_truck = new Truck("EXPIRED", 2020, 20, 85, 90, 80, boost::gregorian::date(2020, 12, 31), strategy);
    BOOST_CHECK_THROW(expired_truck->performInspection(), InspectionException);

    delete truck; // Pamiętaj o zwolnieniu pamięci
    delete bad_brake_truck; // Pamiętaj o zwolnieniu pamięci
    delete bad_tire_truck; // Pamiętaj o zwolnieniu pamięci
    delete bad_cargo_truck; // Pamiętaj o zwolnieniu pamięci
    delete expired_truck; // Pamiętaj o zwolnieniu pamięci
}
