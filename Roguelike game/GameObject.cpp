//
//  GameObject.cpp
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.
//

#include "GameObject.h"

Object::Object()    //Default constructor
{}


Object::Object(int r, int c)        //Placing objects in levels
:o_row(r), o_col(c)
{}


//Weapon implementation

Object::Object(int r, int c, string at, string name, int dex, int dmg, char symbol)
: o_row(r), o_col(c), o_action(at), o_name(name), o_dex(dex), o_dmg(dmg), o_symbol(symbol)
{}


//Scroll implementation

Object::Object(int r, int c, string name, char symbol, char type, int add, string extra)
: o_row(r), o_col(c), o_name(name), o_symbol(symbol), o_type(type), o_add(add), o_extra(extra)
{}


//Weapons

Mace::Mace()    //Default constructor
{}

Mace::Mace(int r, int c)
:Object(r, c, "swings", "mace", 1, 3, ')')  //Mace stats
{}



ShortSword::ShortSword()
:Object(0, 0, "slashes", "short sword", 0, 2, ')')  //Given to the player at the beginning. Coordinates (0,0)
{}

ShortSword::ShortSword(int r, int c)
:Object(r, c, "slashes", "short sword", 0, 2, ')')  //Short Sword stats
{}



LongSword::LongSword()  //Default constructor
{}

LongSword::LongSword(int r, int c)
:Object(r, c, "swings", "long sword", 2, 4, ')')    //Long Sword stats
{}



MagicAxe::MagicAxe()    //Default constructor
{}

MagicAxe::MagicAxe(int r, int c)
:Object(r, c, "chops", "magic axe", 5, 5, ')')      //Magic Axe stats
{}



MagicFangs::MagicFangs()    //Default constructor
{}

MagicFangs::MagicFangs(int r, int c)
:Object(r, c, "strikes", "magic fangs", 4, 2, ')')      //Magic Fangs stats
{}


InfinityBlade::InfinityBlade()  //Default constructor
{}

InfinityBlade::InfinityBlade(int r, int c)
:Object(r, c, "slashes", "The Infinity Blade", 10, 10, '*')     //Infinity Blade stats
{}


DuelInfinityBlade::DuelInfinityBlade()  //Default constructor
{}

DuelInfinityBlade::DuelInfinityBlade(int r, int c)
:Object(r, c, "slashes", "Duel Infinity Blades", 20, 20, '%')   //Duel Infinity Blade
{}


GodlyKatana::GodlyKatana()   //Default constructor
{}

GodlyKatana::GodlyKatana(int r, int c)
:Object(r, c, "slices", "The Godly Katana", 40, 5, '|')    //Godly Katana
{}


DuelGodlyKatana::DuelGodlyKatana()    //Default constructor
{}

DuelGodlyKatana::DuelGodlyKatana(int r, int c)
:Object(r, c, "slices", "Duel Godly Katanas", 80, 10, '=')   //Duel Godly Katana
{}



//Scrolls

Teleport::Teleport()    //Default constructor
{}

Teleport::Teleport(int r, int c)
:Object(r, c, "scroll of teleportation", '?', 't', 0, "You feel your body wrenched in space and time.")     //Scroll of teleportation stats
{}



Armor::Armor()  //Default constructor
{}

Armor::Armor(int r, int c)
:Object(r, c, "scroll of enhance armor", '?', 'a', 1+randInt(3), "Your armor grows stronger.")      //Scroll of enhance armor stats
{}



Strength::Strength()    //Default constructor
{}

Strength::Strength(int r, int c)
:Object(r, c, "scroll of strength", '?', 's', 1+randInt(3), "Your muscles become bigger.")      //Scroll of strength stats
{}



Health::Health()    //Default constructor
{}

Health::Health(int r, int c)
:Object(r, c, "scroll of enhance health", '?', 'h', 3+randInt(6), "You feel your heart beating stronger.")      //Scroll of health stats
{}



Dexter::Dexter()    //Default constructor
{}

Dexter::Dexter(int r, int c)
:Object(r, c, "scroll of enhance dexterity", '?', 'd', 1, "You feel like less of a klutz.")     //Scroll of dexterity stats
{}

