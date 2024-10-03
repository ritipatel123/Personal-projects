//
//  main.cpp
//  project 2
//
//  Created by Riti Patel on 1/17/24.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Constants for plan costs and discounts
    const double EXECUTIVE_COST = 100.00;
    const double BASIC_COST = 50.00;
    const double ADULT_DISCOUNT= 0.00;
    const double CHILD_DISCOUNT = 0.5;
    const double SENIOR_DISCOUNT = 0.75;
    const double ODD_COST= 0.00;
    const double EVEN_COST= 0.00;
    const double EVERYDAY_COST = 25.00;
    const double JUSTONE_COST= 0.00;
    const double REGIONAL_COST = 30.00;
    const double NATIONAL_COST = 50.00;
    const double AUTOPAY_DISCOUNT = 2.00;
    const double AUTOPAY_COUNT= 0.00;
    const double PAPERLESS_BILLING_DISCOUNT = 3.00;
    const double PAPERLESS_BILLING_COUNT= 0.00;

    // Variables to store choices
    string kindOfPlan, typeOfPlan, workoutDays, facilitiesAccess, autopay, paperlessBilling;

    // Getting user input
    cout << "What kind of gym membership plan do you want to buy? ";
    getline(cin,kindOfPlan);

    cout << "What type of gym membership do you want to buy? ";
    getline(cin,typeOfPlan);

    cout << "Which days do you want to workout? ";
    getline(cin, workoutDays);

    cout << "Which facilities do you want to access to? " ;
    getline(cin, facilitiesAccess);

    cout << "Are you on autopay? ";
    getline(cin, autopay);

    cout << "Are you on paperless billing? ";
    getline(cin, paperlessBilling);

    // Calculate the base cost based on the kind of plan
    double baseCost= 0.0;
    if (kindOfPlan == "Executive"){
        baseCost= EXECUTIVE_COST;
    } else if (kindOfPlan == "Basic"){
        baseCost= BASIC_COST;
    } else{
        cout << "Your kind of membership plan is not valid!" << endl;
        exit(1);
    }
    // apply discounts based on the type of plan
    double discount = 0.0;
    if (typeOfPlan == "Child") {
        discount = CHILD_DISCOUNT;
    } else if (typeOfPlan == "Senior") {
        discount = SENIOR_DISCOUNT;
    } else if (typeOfPlan == "Adult"){
        discount= ADULT_DISCOUNT;
    } else {
        cout << "Your type of membership is not valid!"<< endl;
        exit(1);
    }
    // determining the extra cost for everyday access to the gym
    double workoutCost = 0.0;
    if (workoutDays == "Odd Days") {
        workoutCost = ODD_COST;
    } else if (workoutDays == "Even Days") {
        workoutCost = EVEN_COST;
    } else if (workoutDays== "Everyday"){
        workoutCost= EVERYDAY_COST;
    } else{
        cout << "Your membership days are not valid!"<< endl;
        exit(1);
    }
    // determining the extra cost for facilities access
    double facilitiesAccess = 0.0;
    if (workoutDays == "Just One") {
        facilitiesAccess = JUSTONE_COST;
    } else if (workoutDays == "Regional") {
        facilitiesAccess= REGIONAL_COST;
    } else if (workoutDays== "National"){
        facilitiesAccess= NATIONAL_COST;
    } else{
        cout << "Your facilities choice is not valid!"<< endl;
        exit(1);
    }
    // determining the discounts based on autopay
    double autopayDiscount = 0.0;
    if (autopay == "Yes") {
        autopayDiscount = AUTOPAY_DISCOUNT;
    } else if (autopay == "No") {
        autopayDiscount= AUTOPAY_COUNT;
    } else{
        cout << "Your autopay is not valid!"<< endl;
        exit(1);
    }
    // determining the discounts based on paperless billing
    double paperlessBillingDiscount = 0.0;
    if (paperlessBilling == "Yes") {
        paperlessBillingDiscount = PAPERLESS_BILLING_DISCOUNT;
    } else if (paperlessBilling == "No") {
        paperlessBillingDiscount = PAPERLESS_BILLING_COUNT;
    } else{
        cout << "Your paperless billing is not valid!"<< endl;
        exit(1);
    }
    
    // Calculate the total cost
    double totalCost = baseCost * (1.0 - discount) + workoutCost + facilitiesAccess - autopayDiscount - paperlessBillingDiscount;

    // Display the total cost
    cout << "Your"<< kindOfPlan<< "gym membership cost is" << "$" <<totalCost << endl;

    return 0;
}

