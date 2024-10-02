//
//  revision.cpp
//  projectfinal
//
//  Created by Riti Patel on 6/13/24.
//

#include "hash.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cctype>
using namespace std;


bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch) || !isascii(ch) || !isdigit(ch)) {
        inf.unget();
        return false;
    }
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, char& delim, int& length, int& offset)
{
    if (!inf.get(cmd)) {
        cmd = 'x';  // signals end of file
        return true;
    }
    switch (cmd) {
    case '+':
        return inf.get(delim).good();
    case '#':
        {
            char ch;
            return getInt(inf, offset) && inf.get(ch) && ch == ',' && getInt(inf, length);
        }
    case '\r':
    case '\n':
        return true;
    }
    return false;
}


void createRevision(istream& fold, istream& fnew, ostream& frevision) {
    if (!fold || !fnew) {
        
        return;
    }

    // Reading in the files
    string oldFileContents((istreambuf_iterator<char>(fold)), istreambuf_iterator<char>());
    string newFileContents((istreambuf_iterator<char>(fnew)), istreambuf_iterator<char>());

    const int LENGTH = 8;

    HashTable oldFileHashTable; // hash table created
    for (size_t i = 0; i + LENGTH <= oldFileContents.size(); ++i) {
        oldFileHashTable.insert(oldFileContents.substr(i, LENGTH), i);
    } // iterates over starting positions of the LENGTH-substrings in oldFile and adds to hash table

    size_t newFileIndex = 0; // start processing the new file from the beginning
    while (newFileIndex < newFileContents.size()) {
        string currentSegment = newFileContents.substr(newFileIndex, LENGTH);
        unsigned long offset;
        if (oldFileHashTable.contains(currentSegment, offset)) { // if a match was found
            unsigned long bestlen = 0;
            int bestIndex = oldFileHashTable.findBestCopyIndex(oldFileContents, newFileContents, currentSegment, bestlen, newFileIndex);
            frevision << "#" << bestIndex << "," << bestlen << "\n";
            newFileIndex += bestlen;
        } else { // no match found
            size_t nextMatchIndex = newFileIndex + 1;
            while (nextMatchIndex < newFileContents.size()) {
                currentSegment = newFileContents.substr(nextMatchIndex, LENGTH); // next sequence removed
                if (oldFileHashTable.contains(currentSegment, offset)) break; // if you find a match you break out of the loop
                ++nextMatchIndex; // increment where you are searching from
            }

            string toAdd = newFileContents.substr(newFileIndex, nextMatchIndex - newFileIndex); // removes the not matching sequence from newFileContents
            char delimiter = '/'; //  delimiter char
            if (toAdd.find(delimiter) != string::npos) {
                delimiter = ':';
            }

            frevision << "+" << delimiter << toAdd << delimiter << "\n"; // adding to frevision file
            newFileIndex = nextMatchIndex; // move the index
        }
    }
    
}

bool revise(istream& fold, istream& frevision, ostream& fnew) {
    string oldContents((istreambuf_iterator<char>(fold)), istreambuf_iterator<char>()); // oldFile is read and stored into a string

    char command, delimiter; // stores the command and delimeter
    int length = 0, offset = 0;

    while (getCommand(frevision, command, delimiter, length, offset)) { //helper function processes the commands
        if (command == 'x') // end of the file reached
            break;

        if (command == '+') { // adding instructions
            string addition;
            char ch; //intake characters from revision file
            while (frevision.get(ch) && ch != delimiter) {
                addition += ch;
            }
            fnew << addition; // adds the string to new file
        } else if (command == '#') { // copy command
            if (offset >= static_cast<int>(oldContents.size()))
                return false; // makes sure that the offset is within the bounds of the length of the Oldfile and if it's not, return false

            fnew << oldContents.substr(offset, length); // specific substring added to new file from the old file passing the offset and the length of the substring
        } else if (command == '\r' || command == '\n') {
            continue;
        } else { // return false since invalid
            return false;
        }
    }
    return true;
}
