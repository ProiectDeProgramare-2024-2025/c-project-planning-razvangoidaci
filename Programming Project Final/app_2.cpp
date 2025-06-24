#include <iostream>
#include "WishlistManager.h"
#include "InquiryManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    WishlistManager wishlist;
    InquiryManager inquiry;

    if (argc < 2) {
        cout << "\033[1;31m[ERROR]\033[0m Missing command.\n";
        return 1;
    }

    string cmd = argv[1];

    try {
        if (cmd == "view_wishlist") {
            wishlist.displayWishlist();
        } else if (cmd == "add_to_wishlist" && argc == 4) {
            wishlist.addItem(argv[2], stod(argv[3]));
        } else if (cmd == "modify_offer" && argc == 4) {
            wishlist.modifyItem(argv[2], stod(argv[3]));
        } else if (cmd == "remove_from_wishlist" && argc == 3) {
            wishlist.removeItem(argv[2]);
        } else if (cmd == "submit_inquiry") {
            inquiry.submitInquiry(wishlist);
        } else {
            cout << "\033[1;31m[ERROR]\033[0m Invalid command or wrong args.\n";
        }
    } catch (exception& e) {
        cerr << "\033[1;31m[EXCEPTION]\033[0m " << e.what() << "\n";
    }

    return 0;
}
