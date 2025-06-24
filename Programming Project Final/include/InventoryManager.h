#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "Vehicle.h"
#include <string>
#include <vector>

class InventoryManager {
public:
    void displayInventory();
    void addVehicle(const std::string& vin, const std::string& make, const std::string& model, int year, double price, bool available);
    void removeVehicle(const std::string& vin);
    void modifyVehicle(const std::string& field, const std::string& vin, const std::string& value);
    void viewInquiries();
};

#endif 