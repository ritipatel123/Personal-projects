//
//  main.cpp
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.
//


#include "Game.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Game g(15);
    g.play();
}
