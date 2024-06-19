cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# Source files for the main project
set(SOURCE_FILES
        src/main.cpp
        src/Vehicle.cpp
        src/Car.cpp
        src/Truck.cpp
        src/Motorcycle.cpp
        src/Manager.cpp
        src/Inspection/InspectionException.cpp
        src/UserInterface.cpp
        src/Month_controler.cpp
        include/Containers/Month_controler.h)

add_executable(Project ${SOURCE_FILES})

target_include_directories(Project PUBLIC include)

# Find Boost libraries
find_package(Boost 1.65 COMPONENTS unit_test_framework date_time REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(Project ${Boost_LIBRARIES})

# Create a macro to simplify test creation
macro(add_boost_test test_name)
    add_executable(${test_name} test/${test_name}.cpp src/Vehicle.cpp src/Car.cpp src/Truck.cpp src/Motorcycle.cpp src/Manager.cpp)
    target_include_directories(${test_name} PUBLIC include)
    target_link_libraries(${test_name} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_DATE_TIME_LIBRARY})
    add_test(NAME ${test_name} COMMAND ${test_name}
            --report_level=detailed
            --log_level=all
            --color_output=yes)
endmacro()

# Add tests
add_boost_test(CarTest)
add_boost_test(TruckTest)
add_boost_test(MotorcycleTest)
add_boost_test(GarageTest)
add_boost_test(ManagerTest)
add_boost_test(ParkingTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
