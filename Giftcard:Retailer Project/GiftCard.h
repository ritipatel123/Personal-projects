
#include <iostream>
#include <string>


#ifndef GIFTCARD_H
#define GIFTCARD_H

class GiftCard {
private:
    std::string retailerName;
    double amount;

public:
    // Constructor
    GiftCard(std::string retailer, double initialAmount);

    // Getter for retailer name
    std::string getRetailer();

    // Getter and setter for amount
    double getAmount();
    
    void setAmount(double newAmount);

    // Method to reduce the outstanding card amount to zero
    void empty();

    // Method to check if the outstanding card amount is zero
    bool isEmpty();

    // Method to verify if the card can be used to purchase the given amount
    bool canBeUsedToPurchase(double purchaseAmount);
};

#endif // GIFTCARD_H

