#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <memory>
#include <boost/date_time/gregorian/gregorian.hpp>

class InspectionStrategy;

class Vehicle {
protected:
    std::string registration_number;
    int year_of_production;
    double brake_condition; // Wskaźnik stanu hamulców (0-100)
    double tire_condition; // Wskaźnik stanu opon (0-100)
    boost::gregorian::date inspection_expiry_date;

public:
    Vehicle(const std::string& reg_num, int year, double brake_cond, double tire_cond, const boost::gregorian::date& expiry_date);
    virtual ~Vehicle() = default;

    std::string getRegistrationNumber() const;
    int getYearOfProduction() const;
    virtual void performInspection() const = 0;
    virtual int getGarageSpace() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);

    double getBrakeCondition() const;
    double getTireCondition() const;
    boost::gregorian::date getInspectionExpiryDate() const;
};

#endif // VEHICLE_H
