//
//  Dungeon.cpp
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.
//


#include "Dungeon.h"

using namespace std;

Dungeon::Dungeon()
: m_player(nullptr), m_rows(MAXROWS), m_cols(MAXCOLS), endRow(0), endCol(0), m_level(0), m_num(0)   //Player in dungeon impementation at beginning
{
    m_rooms = 6 + randInt(4);   //Random number of rooms from 4 to 7    //Number of rooms
    
    for (int r = 0; r < rows(); r++)
        for (int c = 0; c < cols(); c++)
            grid[r][c] = '#';               //Make grid all '#'s at first
    
    make();     //Make dungeon with rooms and corridors
    
    randomPoint(m_playRows, m_playCols);        //Choose a random point for player
}

Dungeon::Dungeon(int level, Player* pPlayer)
:m_player(pPlayer), m_rows(MAXROWS), m_cols(MAXCOLS), m_level(level), prevRow(0), prevCol(0)    //Player in dungeon impementation at future levels
{
    m_rooms = 6 + randInt(4);   //Random number of rooms from 4 to 7
    
    for (int r = 0; r < rows(); r++)
        for (int c = 0; c < cols(); c++)
            grid[r][c] = '#';               //Make grid all '#'s at first
    
    make();     //Make dungeon with rooms and corridors
    
    randomPoint(m_playRows, m_playCols);        //Choose a random point for player
    
}

Dungeon::~Dungeon()     //Destructor
{
    for (int i = 0; i < m_objects.size(); i++)  //Delete all objects on level
    {
        delete m_objects[i];
    }
    
    delete m_player;    //Delete player
    
    for (int k = 0; k < m_monsters.size(); k++)  //Delete all monsters on level
    {
        delete m_monsters[k];
    }
    
}


Actor* Dungeon::getMonster(int r, int c) const
{
    for (int i = 0; i < m_monsters.size(); i++)
        if (r == m_monsters[i]->row() && c == m_monsters[i]->col())     //Get monster at specific location
            return m_monsters[i];
    
    return nullptr;     //If no monster at location, return a nullptr
}



bool Dungeon::checkForDead()
{
    for (vector<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)   //Look through monster vector to see if any are dead
    {
        Actor* mon = *p;
        
        if (mon->isDead())
        {
            mon->drop(mon->row(), mon->col());      //If one is, have them maybe drop an item
            p = m_monsters.erase(p);            //Erase monster
            return true;
        }
    }
    return false;   //No monsters are dead
}


void Dungeon::display()
{
    for (int i = 0; i < rows(); i++)        //If char in grid is not identifiable, replace it with blank space
        for (int k = 0; k < cols(); k++)
            if (grid[i][k] != ')' && grid[i][k] != '?' && grid[i][k] != '#')
                grid[i][k] = ' ';
    
    
    for (int k = 0; k < m_objects.size(); k++)           //Put the objects on the display
        grid[m_objects[k]->row()][m_objects[k]->col()] = m_objects[k]->symbol();
    
    
    
    if (m_level != 4)                   //Not last level
        grid[endRow][endCol] = '>';     //Make stairs
    else
        grid[m_idol.row()][m_idol.col()] = '&';     //Is the last level. Bring in the idol to win the game
    
    
    for (int i = 0; i < m_monsters.size(); i++)     //Put the monsters on the display
        grid[m_monsters[i]->row()][m_monsters[i]->col()] = m_monsters[i]->symbol();     //With respective symbols

    
    if (m_player != NULL)    //Put in the player first
    {
        char& gridChar = grid[m_player->row()][m_player->col()];
        if (grid[m_player->row()][m_player->col()] != '#')
            gridChar = m_player->symbol();      //If spot is not a wall, put in player symbol
    }
    
    
    
    
    
    for (int r = 0; r < rows(); r++)    //Display the actual dungeon
    {
        for (int c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    
    
    if ((m_level+1) > 5)
    {
        cout << "Secret Level: " << (m_level + 1) << ", Life Points: " << m_player->hp() << ", Armor: " << m_player->arm() << ", Strength: " << m_player->str() << ", Dexterity: " << m_player->mDex() << endl;    //Display Dungeon and player stats for secret level
    }
    else
    {
        cout << "Dungeon Level: " << (m_level + 1) << ", Life Points: " << m_player->hp() << ", Armor: " << m_player->arm() << ", Strength: " << m_player->str() << ", Dexterity: " << m_player->mDex() << endl;    //Display Dungeon and player stats
    }
}


bool Dungeon::addPlayer()   //Bool that adds the player to the dungeon
{
    if (m_player != nullptr)
    {
        m_player->newPoint(this, m_playRows, m_playCols);   //Choose a random new point
        return false;   //Already is a player. Moving the player to new point.
    }
    else
    {
        m_player = new Player(this, m_playRows, m_playCols);    //New player was created and added to dungeon
        return true;
    }
}

bool Dungeon::addMonster(int M) //Add monsters to dungeon
{
    int x = 0, y = 0;
    randomPoint(x, y);  //Choose a random point
    switch (M)
    {
        case 0:
            m_monsters.push_back(new Snakewomen(this, x, y));   //Insert snakewomen on any level
            break;
        case 1:
            m_monsters.push_back(new Goblin(this, x, y));   //Insert goblin on any level
            break;
        case 2:
            m_monsters.push_back(new Bogeyman(this, x, y));     //Insert bogeyman on level 3 or deeper
            break;
        case 3:
            m_monsters.push_back(new Dragon(this, x, y));     //Insert dragon on level 4 or deeper
            break;
        case 4:
            m_monsters.push_back(new Mage(this, x, y));     //Insert Mage on level 5 or deeper
            break;
        default:
            break;
    }
    return true;
    
}


bool Dungeon::moveMonsters(string &action)
{
    bool hit[m_monsters.size()];    //Array of attack bools for each monster. (If each attacked or not)
    
    for (int i = 0; i < m_monsters.size(); i++)
    {
        if (!m_monsters[i]->isSleep())
            hit[i] = m_monsters[i]->move('m', action);  //This tells move function that it is a monster with the 'm'
        if (m_monsters[i]->isSleep())
            m_monsters[i]->changeSleep(-1);     // One turn has pasted so one less turn asleep
    }
    
    for (int k = 0; k < m_monsters.size(); k++) //If a monster attacked the player
    {
        if (hit[k] == true)
            return true;        //If true, computerMessage will be true and display a message
    }
    return false;   //ComputerMessage is false
}


bool Dungeon::nextLevel()       //If player takes stairs to next level
{
    if (m_player->row() == endRow && m_player->col() == endCol)     //If player is standing on a '>'
    {
        return true;
    }
    return false;
}


bool Dungeon::goodMove(int r, int c)    //Whether a move is possible or not
{
    grid[m_player->row()][m_player->col()] = '@';   //Put player on the board in current spot
    
    if(grid[r][c] != '&' && grid[r][c] != ')' &&    //If symbol is none of these, it is a bad move
       grid[r][c] != '?' && grid[r][c] != '>' &&
       grid[r][c] != '*' && grid[r][c] != ' ' && grid[r][c] != '|')
        return false;
    
    for (int i = 0; i < m_monsters.size(); i++)
    {
        if (r == m_monsters[i]->row() && c == m_monsters[i]->col())     //Cant move onto a monster
            return false;
    }
    return true;        //Else, the move is ok
}


bool Dungeon::wall(int r, int c)  //Simply check if spot is a wall
{
    if (grid[r][c] == '#')
        return true;
    return false;
}



bool Dungeon::addItem(int r, int c, int key)    //Add objects to the dungeon using int key
{
    switch (key)
    {
        case 0:
            m_objects.push_back(new Mace(r, c));
            break;
        case 1:
            m_objects.push_back(new ShortSword(r, c));
            break;
        case 2:
            m_objects.push_back(new LongSword(r, c));
            break;
        case 3:
            m_objects.push_back(new MagicAxe(r, c));
            break;
        case 4:
            m_objects.push_back(new MagicFangs(r, c));
            break;
        case 5:
            m_objects.push_back(new Teleport(r, c));
            break;
        case 6:
            m_objects.push_back(new Armor(r, c));
            break;
        case 7:
            m_objects.push_back(new Strength(r, c));
            break;
        case 8:
            m_objects.push_back(new Health(r, c));
            break;
        case 9:
            m_objects.push_back(new Dexter(r, c));
            break;
        case 10:
            m_objects.push_back(new InfinityBlade(r, c));
            break;
        case 11:
            m_objects.push_back(new GodlyKatana(r, c));
            
        default:
            break;
    }
    return true;    //Will always return true
}


bool Dungeon::pickUp(string &item)      //Pick up an object at certain spot
{
    if (m_player->row() == m_idol.row() && m_player->col() == m_idol.col())     //If player is right on the idol
    {
        cout << endl;
        cout << "You pick up the golden idol" << endl;
        cout << "Congratulations, you won!" << endl;
        cout << "Press q to exit game." << endl;

        char ch;
        while (ch != 'q')
        {
            ch = getCharacter();
            if (ch == 'q')
                exit(1);        //Exit game, player has won
        }
        return true;
    }
    if (player()->m_inventory.size() <= 25)     //If inventory is not full (25 or fewer objects)
    {
        for (int i = 0; i < m_objects.size(); i++)
        {
            if (m_objects[i]->row() == m_player->row() && m_objects[i]->col() == m_player->col())   //If player is on an object
            {
                item = "You pick up " + m_objects[i]->name() + '\n';    //Object message
                m_player->holdObjects(m_objects[i]);    //Change m_holding of player
                m_objects[i] = m_objects[m_objects.size()-1];   //Make object being picked up the last item in vector
                m_objects.pop_back();   //When item is picked up, pop it off the dungeon vector
            }
        }
        return true;
    }
    else
    {
        item = "Your inventory is full; you can't pick that up." + '\n';    //More then 25 objects in the inventory
    }
    return false;
}



bool Dungeon::checkObject(int r, int c)   //Checks to make sure no item is already in a spot
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        if ((m_objects[i]->row() == r) && (m_objects[i]->col() == c))
        {
            return false;   //There is an item already there
        }
    }
    return false;   //No item in that spot
}



bool Dungeon::makeRoom(int &row, int &col)
{
    bool fit = true; //Make sure rooms fit in dimensions
    
    int y = 5 + randInt(12);    //Get random y dimensions       //Original: 4, 7
    
    int x = 5 + randInt(12);     //Get random x dimensions      //Original: 4, 7
    
    
    int r = 1 + randInt(MAXROWS-2);  //Get random row spots
    
    int c = 1 + randInt(MAXCOLS-2);  //Get random col spots
    
    row = r;    //Set row
    
    col = c;    //Set col
    
    for (int i = (r - y/2) - 1; i <= (r + y/2) + 1; i++)    //Check rooms using dimensions and starting spots using half dimensions method
    {
        for (int k = (c - x/2) - 1; k <= (c + x/2) + 1; k++)
        {
            if ((i < 0) || (k < 0) || (i > (rows() - 1)) || (k > (cols() - 1 ) || (grid[i][k] != '#'))) //Check if the fit is false
            {
                fit = false;    //Does not fit in dungeon
                break;
            }
        }
    }
    if (!fit)
        return false;
    else
    {
        for (int j = (r - y/2); j <= (r + y/2); j++)        //Make rooms using dimensions and starting spots using half dimensions method again
        {
            for (int l = (c - x/2); l <= (c + x/2); l++)
            {
                if (j < rows() && l < cols())
                {
                    grid[j][l] = ' ';
                }
            }

        }
    }
    m_num++;    //Increment the number of rooms in the dungeon
    return true; //Room has been added
    
}


void Dungeon::randomPoint(int &r, int &c)   //Useful function that picks a random coordinate spot in the dungeon that is open and not a wall, monster or object
{
    while (grid[r][c] != ' ')   //Picks new spot anywhere in dungeon until one is open
    {
        r = 1 + randInt(MAXROWS - 2);
        c = 1 + randInt(MAXCOLS - 2);
    }
    
}



void Dungeon::make()
{
    //Making the dungeon with rooms and corridors
    bool test = false;
    
    int newRow = 0, newCol = 0;
    int pRow = 0, pCol = 0;
    
    
    while (m_num != m_rooms)    //While there are not enough rooms in dungeon
    {
        if (test)   //if a room was made and test is true, get previous row and col of the last room
        {
            pRow = newRow;
            pCol = newCol;
        }
        
        test = makeRoom(newRow, newCol);    //Return true if room was made, false otherwise.
        
        
        if (m_num > 1 && test == true)    //Can now put corridors between rooms
        {
            if (pRow >= newRow) //prev room is under new room                                //EDIT?
            {
                if (pCol > newCol) //preve room is to right of new room
                {
                    for (int r = pRow; r >= newRow; r--)    //Corridor goes up and to the left
                        grid[r][pCol] = ' ';
                    for (int s = pCol; s > newCol; s--)
                        grid[newRow][s] = ' ';
                }
                else
                {
                    for (int r = pRow; r >= newRow; r--)    //Corridor goes up and to the right
                        grid[r][pCol] = ' ';
                    for (int s = pCol; s < newCol; s++)
                        grid[newRow][s] = ' ';

                }
            }
            else if (pRow < newRow)  //if prev room is above new room
            {
                
                if (pCol > newCol)  //if prev room is to the right of new room
                {
                    for (int r = pCol; r >= newCol; r--) //Corridor goes left then down
                        grid[pRow][r] = ' ';
                    for (int s = pRow; s < newRow; s++)
                        grid[s][newCol] = ' ';
                }
                
                else    //if prev room is to the left of the new room
                {
                    for (int r = pCol; r <= newCol; r++) //Corridor goes right then down
                        grid[pRow][r] = ' ';
                    for (int s = pRow; s < newRow; s++)
                        grid[s][newCol] = ' ';
                }
            }

        }
            
    }
    
    if (m_num == m_rooms)   //If there is enough rooms in the dungeon
    {
        int items = 2 + randInt(2); //Put 2 to 3 random items on each level
        for (int i = 0; i < items; i++)
        {
            int sr = 0, sc = 0;
            randomPoint(sr, sc);
        
            int key = 0;
            int choice = randInt(2);    // 50/50 chance of picking one or the other to decide which objects to place
            if (choice == 0)
                key = randInt(3);
            else
                key = 6 + randInt(4);
            
            addItem(sr, sc, key);   //Add random objects to the dungeon
        }
        
        int M = 10 + randInt(3*(m_level+1));     //Put monsters in dungeon      //Original: 5 + randint(3*(m_level+1))
        for (int i = 0; i < M; i++)
        {
            int monster = 0;
            switch (m_level)
            {
                case 2:
                    monster = 3;    //Dragons can not be this early
                    break;
                case 3:
                    monster = 4;
                    break;
                default:
                    monster = 2;   //Bogeymen can not be this early
                    break;
            }
            if (m_level >= 4)
                monster = 5;
            addMonster(randInt(monster));   //Add a random monster
        }
    
    //Finally
    
        if (m_level != 4)   //If not the last level
        {
            randomPoint(endRow, endCol);    //Spot for the stairs
        }
        else    //If it is level 4, time for the idol
        {
            int r, c = 0;
        
            randomPoint(r, c);
        
            Object idol(r, c);  //Put idol object in random spot
        
            m_idol = idol;
        
        }
    
        if (m_level > 1)
        {
            randomPoint(prevRow, prevCol);
        }
    }
}

