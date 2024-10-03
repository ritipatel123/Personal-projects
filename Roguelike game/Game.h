//
//  Game.h
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

#include "utilities.h"
#include "Actor.h"

class Dungeon;

class Game
{
public:
    Game(int goblinSmellDistance);  //Game constructor
    ~Game();
    
    int current() {return m_current; }    //Current level accessor
    
    void play();
    
    
private:
    Dungeon* m_dungeons[500];    //5 Levels deep Dungeon
    
    int m_current;  //Current Level
    
    int m_smell;

};

#endif // GAME_INCLUDED
