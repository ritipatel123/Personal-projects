//
//  Dungeon.h
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.
//

#ifndef CAL
#define CAL


#include "Actor.h"
#include "GameObject.h"
#include "utilities.h"
#include "globals.h"
#include "Game.h"
#include <vector>


class Player;
class Objects;
class Actor;
class Game;


class Dungeon
{
public:
    Dungeon();  //Default constructor
    
    Dungeon(int level, Player* pPlayer);
    
    ~Dungeon();
    
    //Accessors
    
    Game* theGame;
    
    int rows() const {return m_rows; }  //row
    int cols() const {return m_cols; }  //col
    int playRows() const {return m_playRows; }  //Player row
    int playCols() const {return m_playCols; }  //Player col
    
    Player* player() const {return m_player; }
    
    Actor* getMonster(int r, int c) const;
    
    char nextSpot(int r, int c) const {return grid[r][c]; }
    
    bool checkForDead();    //Check for dead monsters
    
    void display(); //Display dungeon
    
    
    //Mutators
    
    bool addPlayer();   //Add player to dungeon
    
    bool addMonster(int M);     //Add monsters to dungeon
    
    bool moveMonsters(string& action);     //Move monsters
    
    bool nextLevel();   //next Level info
    
    bool goodMove(int r, int c);       //Is it a good move?
    
    bool wall(int r, int c);        //Is the next spot a wall?
    
    bool addItem(int r, int c, int key);    //Add item to the dungeon
    
    bool pickUp(string& item);  //Pickup item from dungeon
    
    bool checkObject(int r, int c);
    
    bool makeRoom(int& r, int& c);      //Make the rooms of level
    
    void randomPoint(int &r, int &c);   //Choose random point on current level
    
    void make();    //Make the current dungeon
    
private:
    
    int m_rows;
    int m_cols;
    
    int m_rooms;    //Number of rooms
    int m_num;      //Number of rooms made
    int m_level;    //Which level
    
    
    int m_playRows, m_playCols; //Coordinates of Player
    int endRow, endCol;         //Coordinates of the ending spot
    int prevRow, prevCol;       //Previous row and col
    
    Player* m_player;   //Player pointer
    
    
    Object m_idol;         //On level 4 (The fifth level)
    
    vector<Object*> m_objects;     //Objects on map
    
    vector<Actor*> m_monsters;      //Monsters on map
    
    int numOfItems;     //Number of items on map
    
    char grid[MAXROWS][MAXCOLS];    //The dungeon. A grid of characters
    
    
};


#endif /* defined(__CS_32_Project_3__Dungeon__) */
