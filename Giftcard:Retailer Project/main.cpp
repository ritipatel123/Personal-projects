#include <iostream>
#include <string>
#include <cassert>

#include "GiftCard.h"
#include "Retailer.h"

using namespace std;

int main() {
    // Sample test code working with GiftCard and Retailer
    GiftCard card("BestBuy", 200.0);
    Retailer r("Microsoft Store");

    assert(std::to_string(card.getAmount()) == "200.000000");
    assert(card.getRetailer() == "BestBuy");
    assert(!card.isEmpty());
    assert(!card.canBeUsedToPurchase(300.0));
    assert(card.canBeUsedToPurchase(150.0));
    card.empty();
    assert(!card.canBeUsedToPurchase(10.0));

    card.setAmount(200.0);
    assert(r.getName() == "Microsoft Store");
    assert(!r.purchaseItem("Surface Pro", 999.99, card));
    assert(!r.returnItem("Xbox Series X", 499.99, card));

    GiftCard card1("Microsoft Store", 300.0);
    GiftCard card2("Microsoft Store", 500.0);
   
    
    assert(std::to_string(card1.getAmount()) == "300.000000");
    assert(card1.getRetailer() == "Microsoft Store");
    assert(!card1.isEmpty());
    assert(card1.canBeUsedToPurchase(200.0));
    assert(!card1.canBeUsedToPurchase(400.0));
    card1.empty();
    assert(!card1.canBeUsedToPurchase(10.0));

    card1.setAmount(300.0);
    assert(std::to_string(card2.getAmount()) == "500.000000");
    assert(card2.getRetailer() == "Microsoft Store");
    assert(!card2.isEmpty());
    assert(card2.canBeUsedToPurchase(400.0));
    assert(!card2.canBeUsedToPurchase(600.0));
    card2.empty();
    assert(!card2.canBeUsedToPurchase(10.0));

    cout << "All tests passed!" << endl;
    return 0;
}
