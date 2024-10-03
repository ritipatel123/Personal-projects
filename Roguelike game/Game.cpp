//
//  Game.cpp
//  project 3(2)
//
//  Created by Riti Patel on 5/26/24.
//

// Game.cpp

#include "Game.h"
#include <iostream>

using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
:m_current(0), m_smell(goblinSmellDistance)
{
    
    m_dungeons[0] = new Dungeon();  //Create Dungeon
    
    m_dungeons[0]->addPlayer();     //Add player to the dungeon
}

Game::~Game()
{
    for (int i = 0; i < 5 && m_dungeons[i] != nullptr; i++)     //Deletes each dungeon
        delete m_dungeons[i];
}

void Game::play()   //Actually play the game
{
    Player* ptr = m_dungeons[0]->player();      //Make a pointer to the player on first level
    if (ptr == nullptr)
    {
        m_dungeons[0]->display();       //Display pit with no player
        cout << "There is no player in this pit." << endl;
        return;
    }
    string message;     //Message showing game actions
    
    bool displayMessage = false;    //Player action message
    
    bool computerMessage = false;   //Computer action message
    
    do
    {
        m_dungeons[m_current]->checkForDead();  //Check board for any dead monsters
        
        ptr->heal();    //Give player max health
        
        clearScreen();  //Clear the screen for display
        
        m_dungeons[m_current]->display();   //Display new screen with actors and objects
        
        
        if (displayMessage)     //If player does an action
        {
            cout << endl;
            cout << message << endl;
            displayMessage = false;
        }
        else if (computerMessage)   //If computer does an action
        {
            cout << endl;
            cout << message << endl;
            computerMessage = false;
        }
        
        message = ""; //Restart message
    
        
        char move = getCharacter();     //get keyboard input
        
        if (move == '$')    //To go straight to a certain level
        {
            cout << "Enter Level: ";
            int level;
            cin >> level;
            m_current = (level-1);    //Increase current level
            m_dungeons[m_current] = new Dungeon(m_current, ptr);    //make a new level
            m_dungeons[m_current]->addPlayer();     //Add the player to that level
            
        }
        if (move == '*')    //To automatically get an infinity blade
        {
            ptr->setHold(new InfinityBlade(ptr->row(), ptr->col()));
            clearScreen();
            
            cout << endl;
            cout << "You now hold the legendary Infinity Blade." << endl;
            cout << endl;
            cout << "Use it wisely." << endl;
            
            getCharacter();
        }
        if (move == '|')
        {
            ptr->setHold(new GodlyKatana(ptr->row(), ptr->col()));
            clearScreen();
            
            cout << endl;
            cout << "You now hold the extremely rare Godly Katana." << endl;
            cout << endl;
            cout << "Use it wisely." << endl;
            
            getCharacter();
        }
        
        if (!ptr->isSleep())       //If player is not asleep
        {
            switch (move)       //Move switch statement
            {
                case ARROW_UP:
                case ARROW_DOWN:
                case ARROW_LEFT:
                case ARROW_RIGHT:
                    displayMessage = ptr->move(move, message);      //Move will provide a message for displayMessage
                    break;
                case 'c':
                    ptr->cheat();   //If 'c' is pressed, cheat
                    break;
                case 'w':
                    displayMessage = ptr->displayInvent('w', message);  //Display inventory for weapon (wielding)
                    break;
                case 'r':
                    displayMessage = ptr->displayInvent('r', message);  //Dislay inventory for scroll (reading)
                    break;
                case 'g':
                    displayMessage = m_dungeons[m_current]->pickUp(message);    //If 'g' is pressed, pickup object in that current spot
                    break;
                case 'i':
                    displayMessage = ptr->displayInvent('i', message);      //If 'i' is pressed, display inventory for looking
                    break;
                case '>':
                    if (m_dungeons[m_current]->nextLevel())     //Move to the next level
                    {
                        m_current++;    //Increase current level
                        m_dungeons[m_current] = new Dungeon(m_current, ptr);    //make a new level
                        m_dungeons[m_current]->addPlayer();     //Add the player to that level
                    
                    break;
                    }
                case 'q':
                    exit(1);    //Quit game
                default:
                    break;
            }
        }
        if (ptr->isSleep())         //If player is asleep, decrement turns asleep by one
            ptr->changeSleep(-1);
        
        if (move != '$' && move != '\n')
        {
            computerMessage = m_dungeons[m_current]->moveMonsters(message);     //Get computer/monster actions and move monsters accordingly
        }
        
    }
    while (!m_dungeons[m_current]->player()->isDead());     //Continue cycle while player is still alive
    
    
    clearScreen();                      //Getting this far means player is dead
    m_dungeons[m_current]->display();   //Display last view of the dungeon
    cout << message << endl;
    if (m_dungeons[m_current]->player()->isDead())
        cout << "YOU LOSE!" << endl;
    cout << endl;
    cout << "Press q to exit game." << endl;
    char c;
    
    while (c != 'q')
    {
        c = getCharacter();
    }
    if (c == 'q')
        exit(1);    //If 'q' is pressed, exit the game
    
}
