cmake_minimum_required(VERSION 3.10)

# Configuration parameters of cmake
set(CMAKE_CXX_COMPILER g++) # requires g++ to be available on PATH
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# Source files here
set(SOURCE_FILES
        src/main.cpp
        src/Vehicle.cpp
        include/Vehicle.h
        src/Car.cpp
        include/Car.h
        src/Truck.cpp
        include/Truck.h
        src/Motorcycle.cpp
        include/Motorcycle.h
        include/Containers/Garage.h
        include/Containers/Parking.h
        src/Manager.cpp
        include/Manager.h
        include/Inspection/InspectionException.h
        include/Containers/GarageFullException.h
        include/Inspection/CarInspectionStrategy.h
        include/Inspection/TruckInspectionStrategy.h
        include/Inspection/MotorcycleInspectionStrategy.h
        include/Inspection/InspectionStrategy.h
        include/UserInterface.h
        src/UserInterface.cpp
        include/Inspection/LoaderException.h
        include/Inspection/LoaderException.h
        include/Containers/Container.h
        include/Containers/Container.h
        src/Inspection/InspectionException.cpp
)

add_executable(Project ${SOURCE_FILES})

target_include_directories(Project PUBLIC include)

find_package(Boost 1.65 COMPONENTS unit_test_framework date_time REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(Project ${Boost_LIBRARIES})
