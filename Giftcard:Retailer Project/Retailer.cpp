#include "Retailer.h"
#include <iostream>
#include <string>

using namespace std;

Retailer::Retailer(string retailerName) {
    name = retailerName;
}

string Retailer::getName() {
    return name;
}

bool Retailer::purchaseItem(string item, double cost, GiftCard& card) {
    if (getName() != card.getRetailer()) {
        return false;
    }

    if(cost <= 0){
        return false;
    }
    //if the cost of the item is greater than what balance is on the card
    if(cost > card.getAmount())
        return false;
    
    //you can buy
    int moneyLeft = card.getAmount() - cost;
    card.setAmount(moneyLeft);
    
    return true;
}

bool Retailer::purchaseItem(string item, double cost, GiftCard & card1, GiftCard & card2) {
    if(getName() != card1.getRetailer() || getName() != card2.getRetailer()){
        return false;
    }
    if(cost <= 0){
        return false;
    }
    if (card1.getAmount()<0 || card2.getAmount()<0){
        return false;
    }
    // giftcard can not have negative balances
    //can i put the whole cost on the first card?
    if(card1.getAmount() - cost >= 0) {
        card1.setAmount(card1.getAmount() - cost);
        return true;
    }
    
    // Check if the combined amount of card1 and card2 can cover the item cost
    if (card1.getAmount() + card2.getAmount() >= cost) {
        // Calculate the amount to be deducted from card1 and card2
        double amountFromCard1 = card1.getAmount();
        double amountFromCard2 = cost - amountFromCard1;
        card1.empty();
        card2.setAmount(card2.getAmount() - amountFromCard2);
        
        return true;
    }
    return false;
}

bool Retailer::returnItem(string item, double cost, GiftCard& card) {
    if(card.getRetailer() != getName()){
        return false;
    }
    // accounts for negative cost
    if(cost <= 0){
        return false;
    }
    int newAmount = card.getAmount() + cost;
    card.setAmount(newAmount);
    return true;
}

