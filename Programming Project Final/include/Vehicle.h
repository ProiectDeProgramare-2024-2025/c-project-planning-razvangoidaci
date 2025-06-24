#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle {
    std::string vin;
    std::string make;
    std::string model;
    int year;
    double listPrice;
    bool isAvailable;
};

#endif 