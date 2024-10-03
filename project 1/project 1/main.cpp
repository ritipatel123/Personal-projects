//
//  main.cpp
//  project 1
//
//  Created by Riti Patel on 4/3/24.
//
#include "City.h"
#include "History.h"
#include <iostream>
#include <cassert>
    using namespace std;


int main()
    {
        City ct(3, 3);
        ct.addPlayer(2, 2);
        ct.addTooter(3, 3);
        for (int k = 0; k < 12; k++)
            ct.addTooter(3, 1);
        for (int k = 0; k < 3; k++)
            ct.addTooter(1, 3);
        for (int k = 0; k < 21; k++)
            ct.addTooter(1, 1);
        ct.preachToTootersAroundPlayer();
        int nExisting = ct.tooterCount();
          // For a correct program, the probability of this assertion failing
          // is 0.000006, a 1 in 163435 chance
        assert(nExisting >= 2  &&  nExisting <= 27);
        while(ct.tooterCount() != 0)
            ct.preachToTootersAroundPlayer();
        ct.history().display();
        cout << "===" << endl;
    }
