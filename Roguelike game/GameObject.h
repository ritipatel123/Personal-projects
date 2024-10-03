//
//  GameObject.h
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.

#ifndef __CS_32_Project_3__Objects__
#define __CS_32_Project_3__Objects__

#include <string>
#include "utilities.h"

using namespace std;


class Object
{
    
public:
    
    Object();   //Default constructor
    Object(int r, int c);   //For placing the idol
    
    
    Object(int r, int c, string at, string name, int dex, int dmg, char symbol);    //Weapons
    
    
    Object(int r, int c, string name, char symbol, char type, int add, string extra);   //Scrolls
    
    
    //Accessors
    
    int row() const {return o_row; }
    
    int col() const {return o_col; }
    
    int dex() const {return o_dex; }
    
    int dmg() const {return o_dmg; }
    
    int health() const {return o_health; }
    
    int add() const {return o_add; }
    
    char type() const {return o_type; }
    
    char symbol() const {return o_symbol; }
    
    string name() const {return o_name; }
    
    string action() const {return o_action; }
    
    string extra() const {return o_extra; }
    
    
private:
    int o_row, o_col;
    
    int o_dex, o_dmg, o_add, o_health;
    
    char o_symbol, o_type;
    
    string o_name;
    
    string o_action;
    
    string o_extra;
    
};

//Weapons

class Mace : public Object  //Mace class
{
public:
    Mace();
    Mace(int r, int c);
    ~Mace();
};

class ShortSword : public Object    //Short Sword class
{
public:
    ShortSword();
    ShortSword(int r, int c);
    ~ShortSword();
};

class LongSword : public Object     //Long Sword class
{
public:
    LongSword();
    LongSword(int r, int c);
    ~LongSword();
};

class MagicAxe : public Object      //Magic Axe class
{
public:
    MagicAxe();
    MagicAxe(int r, int c);
    ~MagicAxe();
};

class MagicFangs : public Object    //Magic Fangs class
{
public:
    MagicFangs();
    MagicFangs(int r, int c);
    ~MagicFangs();
};


class InfinityBlade : public Object     //Rare Blade class
{
public:
    InfinityBlade();
    InfinityBlade(int r, int c);
    ~InfinityBlade();
};


class DuelInfinityBlade : public Object     //Duel wield Infinity blades
{
public:
    DuelInfinityBlade();
    DuelInfinityBlade(int r, int c);
    ~DuelInfinityBlade();
};


class GodlyKatana : public Object       //Rare Katana
{
public:
    GodlyKatana();
    GodlyKatana(int r, int c);
    ~GodlyKatana();
};


class DuelGodlyKatana : public Object       //Duel wield Katanas
{
public:
    DuelGodlyKatana();
    DuelGodlyKatana(int r, int c);
    ~DuelGodlyKatana();
};

/*

class DeathTorch : public Object        //Rare Death Torch  MAYBE
{
public:
    DeathTorch();
    DeathTorch(int r, int c);
    ~DeathTorch();
};

*/

class Teleport : public Object      //Teleport scroll class
{
public:
    Teleport();
    Teleport(int r, int c);
    ~Teleport();
};

class Armor : public Object     //Armor scroll class
{
public:
    Armor();
    Armor(int r, int c);
    ~Armor();
};

class Strength : public Object      //Strength scroll class
{
public:
    Strength();
    Strength(int r, int c);
    ~Strength();
};

class Health : public Object        //Health scroll class
{
public:
    Health();
    Health(int r, int c);
    ~Health();
};

class Dexter : public Object        //Dexiterity scroll class
{
public:
    Dexter();
    Dexter(int r, int c);
    ~Dexter();
};


#endif /* defined(__CS_32_Project_3__Objects__) */




