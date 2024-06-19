#ifndef MANAGER_H
#define MANAGER_H

#include "Containers/Container.h"
#include "Vehicle.h"

// Klasa Manager zarządza inspekcjami pojazdów
class Manager {
private:
    Container<Vehicle>& garage; // Referencja do kontenera pojazdów w garażu
    Container<Vehicle>& parking; // Referencja do kontenera pojazdów na parkingu

public:
    // Konstruktor przyjmujący referencje do garażu i parkingu
    Manager(Container<Vehicle>& garage, Container<Vehicle>& parking);

    // Metoda do przeprowadzania inspekcji pojazdów
    void performInspections();
};

#endif // MANAGER_H