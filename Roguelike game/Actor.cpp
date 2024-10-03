//
//  main.cpp
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.
//


#include "Actor.h"
#include "GameObject.h"
#include "Dungeon.h"

/*
 Updates in version 4.1:
 
 1. New Weapon (Godly Katana)
 2. New Duel Infinity Blade and Duel Godly Katana capabilities
 3. Ability to delete weapons from inventory if desired
 4. All monsters can be in all secret levels now
 


Updates in version 4.2:
 
 1. New Terminal Window
 2. New Monster: Mage (holds Infinity Blades)
 3. Big Fixes
 4. Bigger field
 5. New Weapon coming soon : D.T.
 
*/

//Actor implementation

Actor::Actor(Dungeon* level, int r, int c, int hp, Object* holding, int arm, int str, int dex, int odex, int sleep, string name, char symbol)
:m_dungeons(level), m_row(r), m_col(c), m_hp(hp), m_holding(holding), m_arm(arm), m_str(str), m_dex(dex), m_sleep(sleep), m_name(name), m_symbol(symbol), m_dead(false), max_health(hp), a_arm(0), a_str(0), a_dex(0), max_sleep(9), o_dmg(0), o_dex(odex), max_arm(99), max_dex(99), max_str(99)
{}


//Mutators

bool Actor::isDead() const      //Checks if dead
{
    if (hp() <= 0)
        return true;
    else
        return false;
}

bool Actor::isSleep() const     //Checks if asleep
{
    if (m_sleep > 0)
        return true;
    else
        return false;
}


void Actor::changeSleep(int a)      //Changes number of turns asleep
{
    m_sleep += a;
    if (m_sleep > max_sleep)
        m_sleep = max_sleep;
}


bool Actor::checkForPlayer(int r, int c) const      //Checks for player in a particular spot
{
    if (m_dungeons->player()->row() == r && m_dungeons->player()->col() == c)
        return true;
    else
        return false;
}

bool Actor::move(char dir, string &act)     //Movement for either the player or monster if dir passed is a 'm'
{
    if (dir == 'm')
    {
        dir = movePlace(Level()->player()->row(), Level()->player()->col());
    }
    
    switch (dir)
    {
        case ARROW_UP:
        {
            if (row() > 0 && Level()->goodMove(row()-1, col()))
            {
                changePoint(row()-1, col());
                m_move = ARROW_UP;
                return false;
            }
            
            checkHold();
            attack(row()-1, col(), act);        //If there is something in that spot, attack
            return true;
            break;
        }
        case ARROW_LEFT:
        {
            if (col() > 0 && Level()->goodMove(row(), col()-1))
            {
                changePoint(row(), col()-1);
                m_move = ARROW_LEFT;
                return false;
            }
            
            checkHold();
            attack(row(), col()-1, act);        //If there is something in that spot, attack
            return true;
            break;
        }
        case ARROW_RIGHT:
        {
            if (col() < Level()->cols()-1 && Level()->goodMove(row(), col()+1))
            {
                changePoint(row(), col()+1);
                m_move = ARROW_RIGHT;
                return false;
            }
            
            checkHold();
            attack(row(), col()+1, act);        //If there is something in that spot, attack
            return true;
            break;
        }
        case ARROW_DOWN:
        {
            if (row() < Level()->rows()-1 && Level()->goodMove(row()+1, col()))
            {
                changePoint(row()+1, col());
                m_move = ARROW_DOWN;
                return false;
            }
            
            checkHold();
            attack(row()+1, col(), act);        //If there is something in that spot, attack
            return true;
            break;
        }
        default:
            return false;
    }
}

void Actor::newPoint(Dungeon *level, int r, int c)  //Placing actor in a new spot on a new level or current level
{
    m_dungeons = level;
    m_row = r;
    m_col = c;
}

void Actor::setHold(Object *a)     //Set what actor is currently holding
{
    m_holding = a;
}

bool Actor::checkHold()     //Factor in the dexterity and damage of what actor is holding
{
    if (m_holding != nullptr)
    {
        o_dex = m_holding->dex();
        o_dmg = m_holding->dmg();
        return true;
    }
    else
    {
        o_dex = 0;
        o_dmg = 0;
    }
    return false;
}



void Actor::attack(int r, int c, string& at)        //For Monster attacking the player
{
    bool hit = false;
    bool sleep = false;
    
    if (Level()->player()->row() == r && Level()->player()->col() == c)
    {
        Actor* ptrPlayer = Level()->player();       //Make a pointer to the player
        
        int offense = this->dex();      //Monster dex
        int deffense = ptrPlayer->dex() + ptrPlayer->arm();     //Player dex and arm stats
        if (randInt(offense) >= randInt(deffense))
        {
            hit = true;     //The attack was a hit
            
            ptrPlayer->changeHp(-1*(randInt(str()+weapDmg())));
            
            if(getObject()->name() == "magic fangs")    //If weapon is magic fangs, sleep is a factor
            {
                if (randInt(8) == 1)        //O: 5
                {
                    sleep = true;
                    int X = 2 + randInt(5);
                    if (!ptrPlayer->isSleep())
                    {
                        ptrPlayer->changeSleep(X);
                    }
                    else
                    {
                        if (X > intSleep())
                            ptrPlayer->changeSleep(X);
                    }
                }
            }
        }
        if (hit)        //Hit messages
        {
            if (ptrPlayer->isDead())
                at += ("the " + name() + " " + getObject()->action() + " at " + ptrPlayer->name() + ", dealing a final blow." + '\n');
            else if (ptrPlayer->isSleep() && sleep == true)
                at += ("the " + name() + " " + getObject()->action() + " at " + ptrPlayer->name() + " and hits, putting " + ptrPlayer->name() + " to sleep." + '\n');
            else
                at += ("the " + name() + " " + getObject()->action() + " at " + ptrPlayer->name() + " and hits." + '\n');
        }
        else
        {
            at += ("the " + name() + " " + getObject()->action() + " at " + ptrPlayer->name() + " and misses." + '\n');
        }
        
    }
}


int Actor::RowDiff()    //The number of rows from monster to player
{
    int r = Level()->player()->row() - m_row;
    if (r < 0)
        return r *= -1;
    else
        return r;
}

int Actor::ColDiff()    //The number of cols from monster to player
{
    int c = Level()->player()->col() - m_col;
    if (c < 0)
        return c *= -1;
    else
        return c;
}




//Player implementation

Player::Player(Dungeon* level, int r, int c)
:Actor(level, r, c, 20, NULL, 2, 2, 2, 0, 0, "Player", '@' )
{
    holdObjects(new ShortSword);    //Starts with a Short Sword
    setHold(m_inventory[0]);
}



bool Player::displayInvent(char key, string& str)   //If a 'w', 'r' or 'i' is clicked
{
    clearScreen();
    cout << "Currently wielding: " << m_holding->name() << endl;
    
    cout << endl;
    
    cout << m_holding->name() << " damage: " << m_holding->dmg() << endl;
    
    cout << m_holding->name() << " dexterity: " << m_holding->dex() << endl;
    
    cout << endl;

    cout << "Inventory: " << endl;
    int i = 0;
    for (; i < m_inventory.size(); i++)
    {
        char out = i + 'a';
        cout << " " << out << ". " << m_inventory[i]->name() << endl;
    }
    
    char t = getCharacter();
    
    if (t == 'D')
    {
        cout << endl;
        cout << "Select the letter of which weapon you would like to delete: " << endl;
        
        char d = getCharacter();
        
        if (m_inventory[d - 'a']->symbol() == ')' || m_inventory[d - 'a']->symbol() == '*' || m_inventory[d - 'a']->symbol() == '|' )
        {
            if (d != 'a')
            {
                vector<Object*>::iterator del = (m_inventory.begin() + d - 'a');   //spot of weapon of choice
                del = m_inventory.erase(del);
            }
        }
    }
    
    if (key == 'w')     //Looking for a weapon to wield
    {
        if (t >= 'a' && t <= 'z')   //Make sure character is an actual letter
        {
            if (t < (i + 'a'))      //Make sure character corresponds to an item
            {
                if (m_inventory[t - 'a']->symbol() == ')' || m_inventory[t - 'a']->symbol() == '*' || m_inventory[t - 'a']->symbol() == '|')
                {
                    if (m_holding->name() == "The Infinity Blade" && m_inventory[t - 'a']->symbol() == '*')
                    {
                        int count = 0;
                        for (int i = 0; i < m_inventory.size(); i++)
                        {
                            if (m_inventory[i]->symbol() == '*')
                                count++;
                        }
                        if (count >= 2)
                        {
                            clearScreen();
                            cout << endl;
                            cout << "Would you like to duel wield your Infinity Blade?" << endl;
                            cout << endl;
                            cout << "Reply Y or N:" << endl;
                            char reply;
                            cin >> reply;
                            if (reply == 'y')
                                setHold(new DuelInfinityBlade(row(), col()));
                            else
                                ;
                        }
                    }
                    else if (m_holding->name() == "The Godly Katana" && m_inventory[t - 'a']->symbol() == '|')
                    {
                        int num = 0;
                        for (int k = 0; k < m_inventory.size(); k++)
                        {
                            if (m_inventory[k]->symbol() == '|')
                                num++;
                            
                        }
                        if (num >= 2)
                        {
                            clearScreen();
                            cout << endl;
                            cout << "Would you like to duel wield your Godly Katana?" << endl;
                            cout << endl;
                            cout << "Reply Y or N:" << endl;
                            char reply;
                            cin >> reply;
                            if (reply == 'y' || reply == 'Y')
                                setHold(new DuelGodlyKatana(row(), col()));
                            else
                                ;
                        }
                    }
                    else if (m_inventory[t - 'a']->symbol() == '*' && m_holding->symbol() != '%')
                    {
                        setHold(m_inventory[t - 'a']);
                    
                        if (m_inventory[t - 'a']->name() == "The Infinity Blade")
                        {
                            clearScreen();
                    
                            cout << endl;
                            cout << "You now hold the legendary Infinity Blade." << endl;
                            cout << endl;
                            cout << "Use it wisely." << endl;
                    
                            getCharacter();
                        }
                    }
                    else if (m_inventory[t - 'a']->symbol() == '|' && m_holding->symbol() != '=')
                    {
                        
                        setHold(m_inventory[t - 'a']);
                        
                        if (m_inventory[t - 'a']->name() == "The Godly Katana")
                        {
                            clearScreen();
                    
                            cout << endl;
                            cout << "You now hold the extremely rare Godly Katana." << endl;
                            cout << endl;
                            cout << "Use it wisely." << endl;
                        
                            getCharacter();
                        }

                    }
                    else
                    {
                        setHold(m_inventory[t - 'a']);
                    }
                    
                    if (m_holding->symbol() == '%')
                        str = "You are now wielding " + m_holding->name() + '\n';
                    else if (m_holding->symbol() == '=')
                        str = "You are now wielding " + m_holding->name() + '\n';
                    else
                        str = "You are wielding " + m_inventory[t - 'a']->name() + '\n';
                }
                else
                {
                    str = "You can't wield " + m_inventory[t - 'a']->name() + '\n';
                    return true;
                }
            }
        }
    }
    
    if (key == 'r')     //Looking for a scroll to read
    {
        if (t >= 'a' && t <= 'z')   //Make sure character is an actual letter
        {
            if (t < (i + 'a'))      //Make sure character corresponds to an item
            {
                if (m_inventory[t - 'a']->symbol() == '?')
                {
                    str = "You read the scroll called " + m_inventory[t - 'a']->name() + '\n';
                    switch (m_inventory[t - 'a']->type())
                    {
                        case 'h':
                        case 's':
                        case 'a':
                        case 't':
                        case 'd':
                            str += m_inventory[t - 'a']->extra() + '\n';
                            break;
                        default:
                            break;
                    }
                    
                    readScroll(m_inventory[t - 'a']);
                    
                    vector<Object*>::iterator p = (m_inventory.begin() + t - 'a');   //spot of recently read scroll
                    
                    p = m_inventory.erase(p);
                }
                else
                {
                    str = "You can't read a " + m_inventory[t - 'a']->name() + '\n';
                }
            }
        }
    }
    return true;
}


void Player::cheat()    //Change hp to 50 and change strength to 9
{
    cheatHp();
    cheatStr();
}

void Player::readScroll(Object *a)  //Pressing 'r' and choosing a scroll
{
    switch (a->type())
    {
        case 'h':
            changeHp(a->add());     //Add hp
            break;
        case 's':
            changestr(a->add());    //Add str
            break;
        case 'a':
            changeArm(a->add());    //Add arm
            break;
        case 't':
        {
            int x = 1;
            int y = 1;
            Level()->randomPoint(x, y);    //Teleport!!. Choose random point
            changePoint(x, y);          //Change player to that point
            break;
        }
        case 'd':
            changeDex(a->add());    //Add dex
            break;
        default:
            break;
    }
}


void Player::attack(int r, int c, string &at)   //When the player attacks other actors/monsters
{
    bool hit = false;
    bool sleep = false;
    
    char next = Level()->nextSpot(r, c);
    switch (next)
    {
        //If there is a monster in that spot
        case 'S':
        case 'G':
        case 'D':
        case 'B':
        case 'M':
        {
            
            Actor* monster = Level()->getMonster(r, c);     //Make pointer to the monster
    
            int offense = this->dex();      //Player dex (this pointer)
            
            int deffense = monster->dex() + monster->arm();     //Monster dexterity and armor stats
            
            int offenseNum = randInt(offense);
            int deffenseNum = randInt(deffense);
            
            if (offenseNum >= deffenseNum)
            {
                hit = true;
                cout << weapDmg() << endl;
                monster->changeHp(-1*(randInt(str()+weapDmg())));
                
        
                if(getObject()->name() == "magic fangs")    //If monster is a snakewomen with magic fangs, sleep is a factor
                {
                    if (randInt(5) == 1)
                    {
                        sleep = true;
                        int X = 2 + randInt(5);
                        cout << X << endl;
                        
                        if (!monster->isSleep())
                        {
                            monster->changeSleep(X);
                            cout << intSleep() << endl;
                        }
                        else
                        {
                            if (X > intSleep())
                                monster->changeSleep(X);
                        }
                    }
                }
            }
            
            int monHealth = monster->hp();
            
            if (hit)    //If the attack is a hit, display a message
            {
                if (monster->isDead())
                    at += (name() + " " + getObject()->action() + " at " + monster->name() + ", dealing a final blow." + '\n');
        
                else if (monster->isSleep() && sleep == true)
                    at += (name() + " " + getObject()->action() + " at " + monster->name() + " and hits, putting " + monster->name() + " to sleep." + '\n');
        
                else
                    at += (name() + " " + getObject()->action() + " at " + monster->name() + " and hits." + '\n');
                
                
                string points = to_string(monHealth);
                
                at += ('\n' + monster->name() + " Life Points: " + points + '\n');
            }
            else
            {
                at += (name() + " " + getObject()->action() + " at " + monster->name() + " and misses." + '\n');
                
                string points = to_string(monHealth);
                
                at += ('\n' + monster->name() + " Life Points: " + points + '\n');
            }
        }
            break;
        default:        //If spot is a wall and no monster
            break;
    }
}

void Player::heal()     //One in ten chance the player will heal that turn
{
    if (hp() < maxhp())
    {
        if (randInt(10) == 0)
            changeHp(1);
    }
}



//Bogeyman implementation

Bogeyman::Bogeyman(Dungeon* level, int r, int c)
:Actor(level, r, c, 10+randInt(6), new Mace(r, c), 2, (2+randInt(2)), (2+randInt(2)), 0, 0, "Bogeyman", 'B')
{}

Bogeyman::~Bogeyman()
{}

void Bogeyman::drop(int r, int c)
{
    
    if (randInt(10) == 0)   //1 in 10 drop of magic fangs. If no item already there.
    {
        if (!(Level()->checkObject(r, c)))
        {
            Level()->addItem(r, c, 4);
        }
    }
}

bool Bogeyman::checkDist()
{
    if ((RowDiff() + ColDiff() <= 7))   //Distance to player is less than or equal to 5. Smelling mechanism //O: 5
        return true;
    else
        return false;
}

char Bogeyman::movePlace(int r, int c)  //Move a desired direction towards the player if in range
{
    int startr = row();
    int startc = col();
    
    if (!checkDist())       //Check if player in range. Else return nothing and don't move
        return ' ';
    
    else if ((!Level()->wall(startr-1, startc) && (Level()->goodMove(startr-1, startc)) && ((startr - r > 0))) || (checkForPlayer(startr-1, startc)))
        return ARROW_UP;
    else if ((!Level()->wall(startr+1, startc) && (Level()->goodMove(startr+1, startc)) && ((startr - r < 0))) || (checkForPlayer(startr+1, startc)))
        return ARROW_DOWN;
    else if ((!Level()->wall(startr, startc-1) && (Level()->goodMove(startr, startc-1)) && ((startc - c > 0))) || (checkForPlayer(startr, startc-1)))
        return ARROW_LEFT;
    else if ((!Level()->wall(startr, startc+1) && (Level()->goodMove(startr, startc+1)) && ((startr - c < 0))) || (checkForPlayer(startr, startc+1)))
        return ARROW_RIGHT;
    else
        return '0';     //No player, do not move
}


//Snakewomen implementation


Snakewomen::Snakewomen(Dungeon* level, int r, int c)
:Actor(level, r, c, 5+randInt(4), new MagicFangs(r, c), 2, 2, 1, 3, 0, "Snakewomen", 'S')
{}

Snakewomen::~Snakewomen()
{}

void Snakewomen::drop(int r, int c)
{
    
    if (randInt(3) == 1)    //1 in 3 drop of magic fangs of sleep. If no item already there
    {
        if (!(Level()->checkObject(r, c)))
        {
            Level()->addItem(r, c, (5 + randInt(5)));
        }
    }
}


bool Snakewomen::checkDist()
{
    if ((RowDiff() + ColDiff() <= 6))   //Distance to player is less than or equal to 3. Smelling mechanism O: 3
        return true;
    else
        return false;
}


char Snakewomen::movePlace(int r, int c)    //Move a desired direction towards the player if in range
{
    int startr = row();
    int startc = col();
    
    if (!checkDist())       //Check if player in range. Else return nothing and don't move
        return ' ';
    
    else if ((!Level()->wall(startr-1, startc) && (Level()->goodMove(startr-1, startc)) && ((startr - r > 0))) || (checkForPlayer(startr-1, startc)))
        return ARROW_UP;
    else if ((!Level()->wall(startr+1, startc) && (Level()->goodMove(startr+1, startc)) && ((startr - r < 0))) || (checkForPlayer(startr+1, startc)))
        return ARROW_DOWN;
    else if ((!Level()->wall(startr, startc-1) && (Level()->goodMove(startr, startc-1)) && ((startc - c > 0))) || (checkForPlayer(startr, startc-1)))
        return ARROW_LEFT;
    else if ((!Level()->wall(startr, startc+1) && (Level()->goodMove(startr, startc+1)) && ((startr - c < 0))) || (checkForPlayer(startr, startc+1)))
        return ARROW_RIGHT;
    else
        return '0';     //No player, do not move
}


//Dragon implementation


Dragon::Dragon(Dungeon* level, int r, int c)
:Actor(level, r, c, 20+randInt(6), new MagicAxe(r, c), 4, 4, 4, 2, 0, "Dragon", 'D')
{}


Dragon::~Dragon()
{}


void Dragon::drop(int r, int c)
{
    
    if (!(Level()->checkObject(r, c)))      //100% will drop a scroll of some kind, If no item already there.
    {
        int number = 0;
        
        number = randInt(20);
        
        //number = 1;
        
        if (number == 1)
            Level()->addItem(r, c, 10);
        else
            Level()->addItem(r, c, 5+randInt(5));
    }
    
}

bool Dragon::checkDist()
{
    if (RowDiff() + ColDiff() <= 1)     //If player is distance of 1 away. Can not move towards player. No smelling
        return true;
    else
        return false;
}


char Dragon::movePlace(int r, int c)    //Dragon only moves to attack, does not actually move around
{
    int startr = row();
    int startc = col();
    
    if (!checkDist())       //Check if player in range. Else return nothing and don't move

        return ' ';
    
    else if ((!Level()->wall(startr-1, startc) && (Level()->goodMove(startr-1, startc)) && ((startr - r > 0))) || (checkForPlayer(startr-1, startc)))
        return ARROW_UP;
    else if ((!Level()->wall(startr+1, startc) && (Level()->goodMove(startr+1, startc)) && ((startr - r < 0))) || (checkForPlayer(startr+1, startc)))
        return ARROW_DOWN;
    else if ((!Level()->wall(startr, startc-1) && (Level()->goodMove(startr, startc-1)) && ((startc - c > 0))) || (checkForPlayer(startr, startc-1)))
        return ARROW_LEFT;
    else if ((!Level()->wall(startr, startc+1) && (Level()->goodMove(startr, startc+1)) && ((startr - c < 0))) || (checkForPlayer(startr, startc+1)))
        return ARROW_RIGHT;
    else
        return '0';     //Dragon not next to player, do nothing.

}


void Dragon::heal()     //Can heal like the player
{
    if (hp() < maxhp())
    {
        if (randInt(10) == 1)
            changeHp(1);
    }
}



//Goblin implementation

Goblin::Goblin(Dungeon* level, int r, int c)
:Actor(level, r, c, 20+randInt(6), new ShortSword(r, c), 1, 3, 1, 0, 0, "Goblin", 'G')
{}



Goblin::~Goblin()
{}

char Goblin::movePlace(int r, int c)    //Move a desired distance towards a player if in range
{
    int startr = row();
    int startc = col();
    
    
    if (!checkDist())       //Check if player in range. Else return nothing and don't move
        return ' ';
    
    else if ((!Level()->wall(startr-1, startc) && (Level()->goodMove(startr-1, startc)) && ((startr - r > 0))) || (checkForPlayer(startr-1, startc)))
        return ARROW_UP;
    else if ((!Level()->wall(startr+1, startc) && (Level()->goodMove(startr+1, startc)) && ((startr - r < 0))) || (checkForPlayer(startr+1, startc)))
        return ARROW_DOWN;
    else if ((!Level()->wall(startr, startc-1) && (Level()->goodMove(startr, startc-1)) && ((startc - c > 0))) || (checkForPlayer(startr, startc-1)))
        return ARROW_LEFT;
    else if ((!Level()->wall(startr, startc+1) && (Level()->goodMove(startr, startc+1)) && ((startr - c < 0))) || (checkForPlayer(startr, startc+1)))
        return ARROW_RIGHT;
    else
        return '0';
}


bool Goblin::checkDist()       //Could not implement recursive goblin search. Goblin instead has smelling mechanism of 15.
{
    if (RowDiff() + ColDiff() <= 18) //If player is distance of 15 away return true.    O: 15
        return true;
    else
        return false;
}


void Goblin::drop(int r, int c)
{
    if (randInt(3) == 1)    //1 in 3 drop of magic axe or magic fangs of sleep if no item already there
    {
        if (!(Level()->checkObject(r, c)))
        {
            Level()->addItem(r, c, 3+randInt(2));
        }
    }
    else
    {
        int number = 0;
        
        number = randInt(25);
        
        //number = 1;
        
        if (number == 1)
        {
            if (!(Level()->checkObject(r, c)))
            {
                Level()->addItem(r, c, 11);
            }
        }
    }
    
}


bool Goblin::pathExists(int sr, int sc, int er, int ec, int depth)      //Non operational path exists function. Is not called
{

    if (sr == er && sc == ec)         //Check if they equal er and ec. We have solved the maze, return true
        return true;
    
    
    if (depth >= 18)   //Set by the game parameter
        return false;
    
    depth++;

    if ((Level()->nextSpot(sr-1, sc) == ' ') && (pathExists(sr-1, sc, er, ec, depth)))
        return true;

    if ((Level()->nextSpot(sr, sc+1) == ' ') && (pathExists(sr, sc+1, er, ec, depth)))
        return true;

    if ((Level()->nextSpot(sr+1, sc) == ' ') && (pathExists(sr+1, sc, er, ec, depth)))
        return true;

    if ((Level()->nextSpot(sr, sc-1) == ' ') && (pathExists(sr, sc-1, er, ec, depth)))
        return true;

    return false;
}


//Additions for Mage


//Mage implementation

Mage::Mage(Dungeon* level, int r, int c)
:Actor(level, r, c, 5+randInt(3), new InfinityBlade(r, c), 1, 1, 2, 0, 0, "Mage", 'M')
{}



Mage::~Mage()
{}

char Mage::movePlace(int r, int c)    //Move a desired distance towards a player if in range
{
    int startr = row();
    int startc = col();
    
    
    if (!checkDist())       //Check if player in range. Else return nothing and don't move
        return ' ';
    
    else if ((!Level()->wall(startr-1, startc) && (Level()->goodMove(startr-1, startc)) && ((startr - r > 0))) || (checkForPlayer(startr-1, startc)))
        return ARROW_UP;
    else if ((!Level()->wall(startr+1, startc) && (Level()->goodMove(startr+1, startc)) && ((startr - r < 0))) || (checkForPlayer(startr+1, startc)))
        return ARROW_DOWN;
    else if ((!Level()->wall(startr, startc-1) && (Level()->goodMove(startr, startc-1)) && ((startc - c > 0))) || (checkForPlayer(startr, startc-1)))
        return ARROW_LEFT;
    else if ((!Level()->wall(startr, startc+1) && (Level()->goodMove(startr, startc+1)) && ((startr - c < 0))) || (checkForPlayer(startr, startc+1)))
        return ARROW_RIGHT;
    else
        return '0';
}


bool Mage::checkDist()       //Could not implement recursive Mage search. Mage instead has smelling mechanism of 30.
{
    if (RowDiff() + ColDiff() <= 30) //If player is distance of 30 away return true.    O: 15
        return true;
    else
        return false;
}


void Mage::drop(int r, int c)
{
    if (randInt(3) == 1)    //1 in 3 drop of magic axe or magic fangs of sleep if no item already there
    {
        if (!(Level()->checkObject(r, c)))
        {
            Level()->addItem(r, c, 3+randInt(2));
        }
    }
    else
    {
        int number = 0;
        
        number = randInt(15);
        
        //number = 1;
        
        if (number == 1)
        {
            if (!(Level()->checkObject(r, c)))
            {
                Level()->addItem(r, c, 10);     //Drop the Infinity Blade (Maybe Death Torch)
            }
        }
    }
    
}


bool Mage::pathExists(int sr, int sc, int er, int ec, int depth)      //Non operational path exists function. Is not called
{
    
    if (sr == er && sc == ec)         //Check if they equal er and ec. We have solved the maze, return true
        return true;
    
    
    if (depth >= 30)   //Set by the game parameter
        return false;
    
    depth++;
    
    if ((Level()->nextSpot(sr-1, sc) == ' ') && (pathExists(sr-1, sc, er, ec, depth)))
        return true;
    
    if ((Level()->nextSpot(sr, sc+1) == ' ') && (pathExists(sr, sc+1, er, ec, depth)))
        return true;
    
    if ((Level()->nextSpot(sr+1, sc) == ' ') && (pathExists(sr+1, sc, er, ec, depth)))
        return true;
    
    if ((Level()->nextSpot(sr, sc-1) == ' ') && (pathExists(sr, sc-1, er, ec, depth)))
        return true;
    
    return false;
}


