#include "InventoryManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;36m"

vector<Vehicle> readFullInventory() {
    vector<Vehicle> inventory;
    ifstream file("inventory.txt");
    if (!file) {
        return inventory;
    }

    int count;
    file >> count;
    if (file.fail()) {
        return inventory;
    }

    Vehicle v;
    for (int i = 0; i < count; ++i) {
        file >> v.vin >> v.make >> v.model >> v.year >> v.listPrice >> v.isAvailable;
        if (!file.fail()) {
            inventory.push_back(v);
        }
    }
    return inventory;
}

void writeFullInventory(const vector<Vehicle>& inventory) {
    ofstream file("inventory.txt", ios::trunc);
    file << inventory.size() << endl;
    for (const auto& v : inventory) {
        file << v.vin << " " << v.make << " " << v.model << " " << v.year << " " << v.listPrice << " " << v.isAvailable << endl;
    }
}

void InventoryManager::displayInventory() {
    vector<Vehicle> inventory = readFullInventory();
    if (inventory.empty()) {
        cout << YELLOW << "[INFO] Inventory is empty." << RESET << endl;
        return;
    }

    cout << BLUE << "--- Current Vehicle Inventory ---" << RESET << endl;
    for (const auto& v : inventory) {
        cout << "VIN: " << v.vin << ", Make: " << v.make << ", Model: " << v.model
             << ", Year: " << v.year << ", Price: " << GREEN << "$" << fixed << setprecision(2) << v.listPrice << RESET
             << ", Available: " << (v.isAvailable ? "Yes" : "No") << endl;
    }
}

void InventoryManager::addVehicle(const string& vin, const string& make, const string& model, int year, double price, bool available) {
    vector<Vehicle> inventory = readFullInventory();

    for (const auto& v : inventory) {
        if (v.vin == vin) {
            cout << RED << "[ERROR] Vehicle with VIN " << vin << " already exists." << RESET << endl;
            return;
        }
    }

    Vehicle newVehicle = {vin, make, model, year, price, available};
    inventory.push_back(newVehicle);
    writeFullInventory(inventory);

    cout << GREEN << "[SUCCESS] Vehicle added to inventory." << RESET << endl;
}

void InventoryManager::removeVehicle(const string& vin) {
    vector<Vehicle> inventory = readFullInventory();
    size_t original_size = inventory.size();

    inventory.erase(remove_if(inventory.begin(), inventory.end(), [&](const Vehicle& v) {
        return v.vin == vin;
    }), inventory.end());

    if (inventory.size() < original_size) {
        writeFullInventory(inventory);
        cout << GREEN << "[SUCCESS] Vehicle with VIN " << vin << " removed." << RESET << endl;
    } else {
        cout << RED << "[ERROR] Vehicle with VIN " << vin << " not found." << RESET << endl;
    }
}

void InventoryManager::modifyVehicle(const string& field, const string& vin, const string& value) {
    vector<Vehicle> inventory = readFullInventory();
    bool found = false;

    for (auto& v : inventory) {
        if (v.vin == vin) {
            found = true;
            if (field == "listPrice") {
                v.listPrice = stod(value);
            } else if (field == "isAvailable") {
                int status = stoi(value);
                if (status != 0 && status != 1) {
                     cout << RED << "[ERROR] Availability must be 1 (for available) or 0 (for sold)." << RESET << endl;
                     return;
                }
                v.isAvailable = (status == 1);
            } else {
                cout << RED << "[ERROR] Invalid field. Can only be 'listPrice' or 'isAvailable'." << RESET << endl;
                return;
            }
            break;
        }
    }

    if (found) {
        writeFullInventory(inventory);
        cout << GREEN << "[SUCCESS] Vehicle with VIN " << vin << " modified." << RESET << endl;
    } else {
        cout << RED << "[ERROR] Vehicle with VIN " << vin << " not found." << RESET << endl;
    }
}

void InventoryManager::viewInquiries() {
    ifstream file("inquiries.txt");
    if (!file) {
        cout << YELLOW << "[INFO] No inquiries found." << RESET << endl;
        return;
    }
    
    cout << BLUE << "--- Submitted Purchase Inquiries ---" << RESET << endl;
    string date_line, vins_line;
    int inquiryNum = 1;

    while (getline(file, date_line) && getline(file, vins_line)) {
        if (date_line.empty() || vins_line.empty()) continue;
        cout << "Inquiry #" << inquiryNum++ << " | Date: " << date_line << endl;
        cout << "  VINs: " << vins_line << endl;
    }
    cout << "----------------------------------" << endl;
}