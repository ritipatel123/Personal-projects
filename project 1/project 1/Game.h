//
//  game.h
//  project 1
//
//  Created by Riti Patel on 4/7/24.
//

#ifndef GAME_H
#define GAME_H

class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nTooters);
    ~Game();

    // Mutators
    void play();

private:
    City* m_city;
};

int decodeDirection(char dir);



#endif /* game_h */
