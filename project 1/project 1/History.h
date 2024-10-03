//
//  History.h
//  project 1
//
//  Created by Riti Patel on 4/10/24.
//

#ifndef History_h
#define History_h
#include "globals.h"

class City;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_Rows;
    int m_Cols;
    int grid[MAXROWS][MAXCOLS];
};


#endif /* History_h */
