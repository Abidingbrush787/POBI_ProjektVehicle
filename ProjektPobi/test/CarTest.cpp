#define BOOST_TEST_MODULE CarTest
#include <boost/test/included/unit_test.hpp>
#include "Car.h"
#include "Inspection/CarInspectionStrategy.h"
#include <boost/date_time/gregorian/gregorian.hpp>

BOOST_AUTO_TEST_CASE(CarCreationTest) {
    boost::gregorian::date expiry_date(2025, 12, 31);
    auto strategy = std::make_shared<CarInspectionStrategy>();
    Car* car = new Car("ABC123", 2020, 4, 85, 90, 80, expiry_date, strategy);

    BOOST_CHECK_EQUAL(car->getRegistrationNumber(), "ABC123");
    BOOST_CHECK_EQUAL(car->getYearOfProduction(), 2020);
    BOOST_CHECK_EQUAL(car->getBrakeCondition(), 85);
    BOOST_CHECK_EQUAL(car->getTireCondition(), 90);
    BOOST_CHECK_EQUAL(car->getEngineCondition(), 80);
    BOOST_CHECK_EQUAL(car->getGarageSpace(), 2);
    delete car;
}

BOOST_AUTO_TEST_CASE(CarInspectionTest) {
    boost::gregorian::date expiry_date(2025, 12, 31);
    auto strategy = std::make_shared<CarInspectionStrategy>();
    Car* car = new Car("ABC123", 2020, 4, 85, 90, 80, expiry_date, strategy);

    BOOST_CHECK_NO_THROW(car->performInspection());

    Car* old_car = new Car("XYZ987", 1990, 4, 85, 90, 80, expiry_date, strategy);
    BOOST_CHECK_THROW(old_car->performInspection(), InspectionException);
    delete car;
    delete old_car;
}
