//
//  City.h
//  project 1
//
//  Created by Riti Patel on 4/10/24.
//

#ifndef City_h
#define City_h

#include <string>
#include "History.h"
#include "globals.h"

class Player;
class Tooter;

class City
{
public:
    // Constructor/destructor
    City(int nRows, int nCols);
    ~City();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    History& history();
    bool    isPlayerAt(int r, int c) const;
    int     tooterCount() const;
    int     nTootersAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

    // Mutators
    bool addTooter(int r, int c);
    bool addPlayer(int r, int c);
    void preachToTootersAroundPlayer();
    void moveTooters();

private:
    int     m_rows;
    int     m_cols;
    History m_history;
    Player* m_player;
    Tooter* m_tooters[MAXTOOTERS];
    int     m_nTooters;

    // Helper functions
    bool isInBounds(int r, int c) const;
};



#endif /* City_h */
