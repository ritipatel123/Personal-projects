//
//  history.cpp
//  project 1
//
//  Created by Riti Patel on 4/3/24.
//

#include "History.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols) {
    
    m_Rows = nRows;
    m_Cols = nCols;

    for (int r = 0; r < m_Rows; r++) {
        for (int c = 0; c < m_Cols; c++) {
            grid[r][c] = 0;
        }
    }
}

bool History::record(int r, int c) {
    if (r < 1 || r > m_Rows || c < 1 || c > m_Cols) {
        return false;
    } else {
        if (grid[r - 1][c - 1] == '.') {
            grid[r - 1][c - 1] = 'A';
        } else if (grid[r - 1][c - 1] == 'Z') {
            grid[r - 1][c - 1] = 'Z';
        }
        else {
            grid[r - 1][c - 1]++;
        }
    }
    return true;
}

void History::display() const {
    clearScreen();

    for (int r = 0; r < m_Rows; r++) {
        for (int c = 0; c < m_Cols; c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
