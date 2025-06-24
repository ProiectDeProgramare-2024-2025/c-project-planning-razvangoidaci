#ifndef WISHLISTMANAGER_H
#define WISHLISTMANAGER_H

#include <string>
#include <vector>

struct WishlistItem {
    std::string vin;
    double offeredPrice;
};

class WishlistManager {
public:
    std::vector<WishlistItem> getWishlist();
    void displayWishlist();
    void addItem(const std::string& vin, double price);
    void modifyItem(const std::string& vin, double newPrice);
    void removeItem(const std::string& vin);
    void clearWishlist();
    bool isWishlistEmpty();
};

#endif

