#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <memory>
#include <boost/date_time/gregorian/gregorian.hpp>

using grDate = boost::gregorian::date;
// Klasa abstrakcyjna reprezentująca pojazd
class InspectionStrategy;

class Vehicle {
protected:
    std::string registration_number; // Numer rejestracyjny pojazdu
    int year_of_production; // Rok produkcji pojazdu
    double brake_condition; // Stan hamulców (0-100)
    double tire_condition; // Stan opon (0-100)
    grDate inspection_expiry_date; // Data ważności przeglądu

public:
    Vehicle(const std::string& reg_num, int year, double brake_cond, double tire_cond, const grDate& expiry_date);
    virtual ~Vehicle() = default;

    // Metody dostępowe (gettery)
    std::string getRegistrationNumber() const;
    int getYearOfProduction() const;
    double getBrakeCondition() const;
    double getTireCondition() const;
    grDate getInspectionExpiryDate() const;

    // Metody wirtualne do zaimplementowania w klasach pochodnych
    virtual void performInspection() const = 0;
    virtual int getGarageSpace() const = 0;

    // Operator wyjścia
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);
};

#endif // VEHICLE_H
