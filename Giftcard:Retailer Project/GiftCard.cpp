#include "GiftCard.h"
#include <string>
#include <iostream>
 
using namespace std;

GiftCard::GiftCard(string r, double initialAmount) {
    retailerName = r;
    amount = initialAmount;
}

string GiftCard::getRetailer() {
    return retailerName;
}

double GiftCard::getAmount() {
    return amount;
}

void GiftCard::setAmount(double newAmount) {
    amount = newAmount;
}

void GiftCard::empty() {
    amount = 0.0;
}

bool GiftCard::isEmpty() {
    return amount <= 0.0;
}

bool GiftCard::canBeUsedToPurchase(double purchaseAmount) {
    if (purchaseAmount <= 0.0 || purchaseAmount > getAmount()) {
        return false;
    }
    
    return true;
}

