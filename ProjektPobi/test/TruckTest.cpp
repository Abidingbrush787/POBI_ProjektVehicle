#define BOOST_TEST_MODULE TruckTest
#include <boost/test/included/unit_test.hpp>
#include "Truck.h"
#include "Inspection/TruckInspectionStrategy.h"
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

    Truck* old_truck = new Truck("XYZ987", 1990, 20, 85, 90, 80, expiry_date, strategy);
    BOOST_CHECK_THROW(old_truck->performInspection(), InspectionException);

    delete truck; // Pamiętaj o zwolnieniu pamięci
    delete old_truck; // Pamiętaj o zwolnieniu pamięci
}
