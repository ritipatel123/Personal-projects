#ifndef RETAILER_H
#define RETAILER_H

#include <string>
#include "GiftCard.h"

class Retailer {
private:
    std::string name;

public:
    Retailer(std::string retailerName);

    std::string getName();
    bool purchaseItem(std::string item, double cost, GiftCard & card);
    bool purchaseItem(std::string item, double cost, GiftCard & card1, GiftCard & card2);
    bool returnItem(std::string item, double cost, GiftCard & card);
};

#endif
