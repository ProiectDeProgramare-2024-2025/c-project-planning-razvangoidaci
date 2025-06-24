#ifndef INQUIRYMANAGER_H
#define INQUIRYMANAGER_H

#include "WishlistManager.h"
#include <string>
#include <vector>

struct Date {
    int day, month, year;
    static Date getToday();
    std::string toString() const;
};

class PurchaseInquiry {
public:
    std::vector<std::string> vinList;
    Date inquiryDate;

    void fromWishlist(const std::vector<WishlistItem>& wishlist);
    void saveToFile(const std::string& filename) const;
};

class InquiryManager {
public:
    void submitInquiry(WishlistManager& wishlistManager);
};

#endif
