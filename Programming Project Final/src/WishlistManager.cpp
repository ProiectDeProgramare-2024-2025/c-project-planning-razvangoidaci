#include "WishlistManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<WishlistItem> WishlistManager::getWishlist() {
    vector<WishlistItem> list;
    ifstream file("wishlist.txt");
    WishlistItem item;

    if (!file) {
        cerr << "\033[1;31m[ERROR]\033[0m Could not open wishlist.txt\n";
        return list;
    }

    while (file >> item.vin >> item.offeredPrice) {
        list.push_back(item);
    }

    return list;
}

void WishlistManager::displayWishlist() {
    auto list = getWishlist();
    if (list.empty()) {
        cout << "\033[1;33m[INFO]\033[0m Wishlist is empty.\n";
        return;
    }

    cout << "\033[1;36m=== Your Wishlist ===\033[0m\n";
    for (const auto& item : list) {
        cout << "VIN: " << item.vin
             << " | Offered Price: \033[1;32m$" << fixed << setprecision(2) << item.offeredPrice << "\033[0m\n";
    }
}

void WishlistManager::addItem(const string& vin, double price) {
    auto list = getWishlist();
    for (const auto& item : list) {
        if (item.vin == vin) {
            cout << "\033[1;31m[ERROR]\033[0m VIN already exists in wishlist.\n";
            return;
        }
    }

    ofstream file("wishlist.txt", ios::app);
    if (!file) {
        cerr << "\033[1;31m[ERROR]\033[0m Could not open wishlist.txt\n";
        return;
    }

    file << vin << " " << price << "\n";
    cout << "\033[1;32m[SUCCESS]\033[0m Vehicle added.\n";
}

void WishlistManager::modifyItem(const string& vin, double newPrice) {
    auto list = getWishlist();
    bool found = false;

    for (auto& item : list) {
        if (item.vin == vin) {
            item.offeredPrice = newPrice;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\033[1;31m[ERROR]\033[0m VIN not found.\n";
        return;
    }

    ofstream file("wishlist.txt", ios::trunc);
    for (const auto& item : list) {
        file << item.vin << " " << item.offeredPrice << "\n";
    }

    cout << "\033[1;32m[SUCCESS]\033[0m Offer updated.\n";
}

void WishlistManager::removeItem(const string& vin) {
    auto list = getWishlist();
    auto it = remove_if(list.begin(), list.end(), [&](const WishlistItem& item) {
        return item.vin == vin;
    });

    if (it == list.end()) {
        cout << "\033[1;31m[ERROR]\033[0m VIN not found.\n";
        return;
    }

    list.erase(it, list.end());
    ofstream file("wishlist.txt", ios::trunc);
    for (const auto& item : list) {
        file << item.vin << " " << item.offeredPrice << "\n";
    }

    cout << "\033[1;32m[SUCCESS]\033[0m Vehicle removed.\n";
}

void WishlistManager::clearWishlist() {
    ofstream file("wishlist.txt", ios::trunc);
}

bool WishlistManager::isWishlistEmpty() {
    return getWishlist().empty();
}

