#include <iostream>
#include <string>
#include <stdexcept>
#include "InventoryManager.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[1;31m"

void printUsage() {
    cout << "Usage:\n";
    cout << "  app_1.exe view_inventory\n";
    cout << "  app_1.exe add_vehicle <vin> <make> <model> <year> <price> <available (1/0)>\n";
    cout << "  app_1.exe remove_vehicle <vin>\n";
    cout << "  app_1.exe modify_vehicle <field> <vin> <value>\n";
    cout << "  app_1.exe view_inquiries\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << RED << "[ERROR] Missing command." << RESET << endl;
        printUsage();
        return 1;
    }

    InventoryManager manager;
    string command = argv[1];

    try {
        if (command == "view_inventory") {
            manager.displayInventory();
        } else if (command == "add_vehicle" && argc == 8) {
            manager.addVehicle(argv[2], argv[3], argv[4], stoi(argv[5]), stod(argv[6]), stoi(argv[7]));
        } else if (command == "remove_vehicle" && argc == 3) {
            manager.removeVehicle(argv[2]);
        } else if (command == "modify_vehicle" && argc == 5) {
            manager.modifyVehicle(argv[2], argv[3], argv[4]);
        } else if (command == "view_inquiries") {
            manager.viewInquiries();
        } else {
            cout << RED << "[ERROR] Invalid command or wrong number of arguments." << RESET << endl;
            printUsage();
        }
    } catch (const exception& e) {
 
        cerr << RED << "[EXCEPTION] Invalid number format provided for price, year, or availability." << RESET << endl;
        return 1;
    }

    return 0;
}