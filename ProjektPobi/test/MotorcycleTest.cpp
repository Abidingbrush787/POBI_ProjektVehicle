#define BOOST_TEST_MODULE MotorcycleTest
#include <boost/test/included/unit_test.hpp>
#include "Motorcycle.h"
#include "Inspection/MotorcycleInspectionStrategy.h"
#include <boost/date_time/gregorian/gregorian.hpp>

BOOST_AUTO_TEST_CASE(MotorcycleCreationTest) {
    boost::gregorian::date expiry_date(2025, 12, 31);
    auto strategy = std::make_shared<MotorcycleInspectionStrategy>();
    Motorcycle* motorcycle = new Motorcycle("GHI789", 2020, 600, 85, 90, 80, expiry_date, strategy);

    BOOST_CHECK_EQUAL(motorcycle->getRegistrationNumber(), "GHI789");
    BOOST_CHECK_EQUAL(motorcycle->getYearOfProduction(), 2020);
    BOOST_CHECK_EQUAL(motorcycle->getBrakeCondition(), 85);
    BOOST_CHECK_EQUAL(motorcycle->getTireCondition(), 90);
    BOOST_CHECK_EQUAL(motorcycle->getFrameCondition(), 80);
    BOOST_CHECK_EQUAL(motorcycle->getGarageSpace(), 1);

    delete motorcycle; // Pamiętaj o zwolnieniu pamięci
}

BOOST_AUTO_TEST_CASE(MotorcycleInspectionTest) {
    boost::gregorian::date expiry_date(2025, 12, 31);
    auto strategy = std::make_shared<MotorcycleInspectionStrategy>();
    Motorcycle* motorcycle = new Motorcycle("GHI789", 2020, 600, 85, 90, 80, expiry_date, strategy);

    BOOST_CHECK_NO_THROW(motorcycle->performInspection());

    Motorcycle* old_motorcycle = new Motorcycle("XYZ987", 1990, 600, 85, 90, 80, expiry_date, strategy);
    BOOST_CHECK_THROW(old_motorcycle->performInspection(), InspectionException);

    delete motorcycle; // Pamiętaj o zwolnieniu pamięci
    delete old_motorcycle; // Pamiętaj o zwolnieniu pamięci
}
