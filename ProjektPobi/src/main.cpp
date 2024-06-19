#include "../include/Containers/Garage.h"
#include "Containers/Parking.h"
#include "UserInterface.h"

int main() {
    Garage garage(10);
    Parking parking(100);

    UserInterface ui(garage, parking);
    ui.showMenu();

    return 0;
}
