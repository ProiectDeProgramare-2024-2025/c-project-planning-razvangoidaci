#include "InquiryManager.h"
#include <ctime>
#include <iostream>
#include <fstream>


using namespace std;

Date Date::getToday() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    return {t->tm_mday, t->tm_mon + 1, t->tm_year + 1900};
}

std::string Date::toString() const {
    return std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
}

void PurchaseInquiry::fromWishlist(const std::vector<WishlistItem>& wishlist) {
    for (const auto& item : wishlist)
        vinList.push_back(item.vin);
    inquiryDate = Date::getToday();
}

void PurchaseInquiry::saveToFile(const string& filename) const {
    ofstream out(filename, ios::app);
    if (!out) {
        cerr << "\033[1;31m[ERROR]\033[0m Could not open " << filename << "\n";
        return;
    }

    out << inquiryDate.toString() << "\n";
    for (size_t i = 0; i < vinList.size(); ++i) {
        out << vinList[i];
        if (i < vinList.size() - 1) out << " ";
    }
    out << "\n";
}

void InquiryManager::submitInquiry(WishlistManager& wishlistManager) {
    auto wishlist = wishlistManager.getWishlist();
    if (wishlist.empty()) {
        cout << "\033[1;33m[INFO]\033[0m Wishlist is empty.\n";
        return;
    }

    PurchaseInquiry inquiry;
    inquiry.fromWishlist(wishlist);
    inquiry.saveToFile("inquiries.txt");

    wishlistManager.clearWishlist();
    cout << "\033[1;32m[SUCCESS]\033[0m Inquiry submitted.\n";
}

