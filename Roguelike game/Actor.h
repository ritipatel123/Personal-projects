//
//  Actor.h
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.

#ifndef CS_32_Project_3_Actors_h
#define CS_32_Project_3_Actors_h

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "Dungeon.h"
#include "GameObject.h"
#include "utilities.h"
#include "Game.h"

class Dungeon;
class Object;
class Game;


class Actor
{
public:
    Actor(Dungeon* level, int r, int c, int hp, Object* holding, int arm, int str, int dex, int odex, int sleep, string name, char symbol); //Constructor
    
    virtual ~Actor() { delete m_holding; }  //Destructor
    
    //Accessors
    
    int row() const { return m_row; }
    int col() const { return m_col; }
    int hp() const { return m_hp; }
    int arm() const { return m_arm + a_arm; }
    int str() const { return m_str + a_str; }
    int dex() const { return m_dex + a_dex + o_dex; }
    int mDex() const { return m_dex + a_dex; }
    int weapDmg() const {return o_dmg; }
    
    int maxhp() const { return max_health; }
    int intSleep() const {return m_sleep; }
    
    string name() const { return m_name; }
    char symbol() const { return m_symbol; }
    
    bool isSleep() const;
    
    bool isDead() const;
    
    char playerMove() const { return m_move; }
    
    
    Object* getObject() const { return m_holding; }
    
    Dungeon* Level() const { return m_dungeons; }

    
    //Mutators
    
    void changeHp(int a) {m_hp += a; if (hp() > max_health) m_hp = max_health; }
    void changeArm(int a) {a_arm += a; if (arm() > max_arm) m_arm = max_arm; }
    void changestr(int a) {a_str += a; if (str() > max_str) m_str = max_str; }
    void changeDex(int a) {a_dex += a; if (dex() > max_dex) m_dex = max_dex; }
    
    void changeSleep(int a);
    
    
    void cheatHp() {m_hp = 50; max_health = 50; }   //Cheating function
    void cheatStr() {m_str = 9; }   //Cheating function
    void changePoint(int r, int c) {m_row = r; m_col = c; }
    
    
    bool checkForPlayer(int r, int c) const;
    bool move(char dir, string &act);
    void newPoint(Dungeon* level, int r, int c);
    
    
    void setHold(Object* a);
    bool checkHold();
    
    
    virtual void heal() {} //Default implementation
    virtual void attack(int r, int c, string& at);  //Default implementation
    virtual void drop(int r, int c) {} //Default implementation
    virtual char movePlace(int r, int c) {return ' '; } //Default implementation
    virtual bool checkDist() {return true; }    //Default implementation
    
    
    int RowDiff();
    int ColDiff();
    
    Object* m_holding;      //Object pointer to the current object
    
    
private:
    int m_row;  //row
    int m_col;  //col
    int m_hp, m_str, m_arm, m_dex;  //actor attributes
    int rDiff, cDiff;   //Difference in row and col
    
    int m_sleep, max_sleep;        //sleeping
    
    int a_arm, a_str, a_dex;     //improvement from scrolls
    
    int o_dmg, o_dex;   //object attributes
    
    int max_health, max_arm, max_dex, max_str;     //max stats
    
    string m_name;  //Names
    
    char m_symbol;  //Symbols
    
    bool m_dead;
    
    char m_move;
    
    Dungeon* m_dungeons;    //Dungeon pointer to the current dungeon
    
};


class Player : public Actor //Player class
{
public:
    
    Player(Dungeon* level, int r, int c);   //Player constructor
    virtual ~Player() {}
    
    //Accessors
    int objects() const { return m_objects; }   //objects in inventory
    bool displayInvent(char key, string& str);  //Display inventory
    
    //Mutators
    void addObjects() {m_objects++; }
    void holdObjects(Object* a) {m_inventory.push_back(a); }
    void cheat();   //Cheat. Give player more health and strength
    void readScroll(Object* a);
    
    virtual void attack(int r, int c, string& at);  //Attack monsters
    virtual void heal();    //Heal. 1/10 chance to heal every turn
    
    vector<Object*> m_inventory;    //Players inventory
                                                       
private:
    
    Actor* m_monsters;
    
    int m_objects;  //number of objects Player has
    
    
};

class Bogeyman : public Actor   //Bogeyman class
{
public:
    Bogeyman(); //Bogeyman default constructor
    Bogeyman(Dungeon* level, int r, int c);     //Constructor for placing in a level
    virtual char movePlace(int r, int c);
    virtual bool checkDist();
    virtual void drop(int r, int c);
    
    virtual ~Bogeyman();
    
private:
    
};

class Snakewomen : public Actor     //Snakewomen class
{
public:
    Snakewomen();   //Snakewomen default constructor
    Snakewomen(Dungeon* level, int r, int c);       //Constructor for placing in a level
    virtual char movePlace(int r, int c);
    virtual bool checkDist();
    virtual void drop(int r, int c);
    
    virtual ~Snakewomen();
};

class Dragon : public Actor     //Dragon class
{
public:
    Dragon();   //Dragon default constructor
    Dragon(Dungeon* level, int r, int c);   //Constructor for placing in a level
    virtual char movePlace(int r, int c);
    virtual bool checkDist();
    virtual void drop(int r, int c);
    virtual void heal();
    
    virtual ~Dragon();
};

class Goblin : public Actor     //Goblin class
{
public:
    Goblin();   //Goblin default constructor
    Goblin(Dungeon* level, int r, int c);       //Constructor for placing in a level
    virtual char movePlace(int r, int c);
    virtual bool checkDist();
    virtual void drop(int r, int c);
    
    bool pathExists(int sr, int sc, int er, int ec, int depth);     //Added function for recusive search. Not operational
    
    virtual ~Goblin();
};

//Additions

class Mage : public Actor       //Mage class
{
public:
    Mage();    //Mage defaul constructor
    Mage(Dungeon* level, int r, int c);         //Constructor for placing in a level
    virtual char movePlace(int r, int c);
    virtual bool checkDist();
    virtual void drop(int r, int c);
    
    bool pathExists(int sr, int sc, int er, int ec, int depth);     //Added function for recursive search
    
    virtual ~Mage();
    
};

#endif
