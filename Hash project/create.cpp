//
//  create.cpp
//  project5
//
//  Created by Riti Patel on 6/11/24.
//
#include <stdio.h>
#include "hash.h"
#include <iostream>
#include <fstream>
#include <sstream>  // for istringstream and ostringstream
#include <string>
#include <cassert>
#include <algorithm>
#include <iterator>
using namespace std;
using namespace std;
void createRevision(istream& fold, istream& fnew, ostream& fdiff);
bool revise(istream& fold, istream& fdiff, ostream& fnew);



void createRevision(istream& fold, istream& fnew, ostream& fdiff) {
    size_t hashnum = 8;
    // Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
    //old string
    char c;
    string oldString = "";
    while (fold.get(c))
    {
        oldString += c;
    }
    //new string
    string newString = "";
    while (fnew.get(c))
    {
        newString += c;
    }
    
    //if the file is too big then increase the hash size
    if(newString.length() > 50000)
    {
        hashnum = 32;
    }
    
    //if both are same
    if(oldString == newString || newString.length() == 0)
    {
        fdiff << '\n';//should you do this
        return;
    }
    
}
bool revise(istream& fold, istream& frevision, ostream& fnew) {
        // Read the entire contents of the original file into a string
        string originalContent((istreambuf_iterator<char>(fold)), istreambuf_iterator<char>());

        // Loop through the revision file and apply instructions
        char cmd;
        char delim;
        int offset, length;

        while (getCommand(frevision, cmd, delim, length, offset)) {
            if (cmd == '+') {
                // Add instruction: Read characters from frevision and write them to fnew
                while (length--) {
                    char ch;
                    if (!frevision.get(ch)) {
                        // Error: Unable to read character from revision file
                        return false;
                    }
                    fnew << ch;
                }
            } else if (cmd == '#') {
                // Copy instruction: Copy characters from originalContent to fnew
                if (offset + length > originalContent.size() || offset < 0 || length < 0) {
                    // Error: Invalid offset or length
                    return false;
                }
                fnew << originalContent.substr(offset, length);
            } else if (cmd == '\n' || cmd == '\r') {
                // Do-nothing instruction: Skip
            } else {
                // Error: Invalid instruction
                return false;
            }
        }

        return true;
    }
bool runtest(string oldName, string newName, string revisionName, string newName2) {
    if (revisionName == oldName || revisionName == newName || newName2 == oldName || newName2 == revisionName || newName2 == newName) {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile) {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile) {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream revisionFile(revisionName, ios::binary);
    if (!revisionFile) {
        cerr << "Cannot create " << revisionName << endl;
        return false;
    }
    createRevision(oldFile, newFile, revisionFile);
    revisionFile.close();

    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream revisionFile2(revisionName, ios::binary);
    if (!revisionFile2) {
        cerr << "Cannot read the " << revisionName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2) {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(revise(oldFile, revisionFile2, newFile2));
    newFile2.close();

    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile) {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if (!equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(), istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>())) {
        cerr << newName2 << " is not identical to " << newName << "; test FAILED" << endl;
        return false;
    }
    return true;
}


int main() {
    assert(runtest("/Users/ritipatel/Desktop/p4test/warandpeace1.txt", "/Users/ritipatel/Desktop/p4test/warandpeace2.txt", "/Users/ritipatel/Desktop/p4test/myrevisionfile.txt", "/Users/ritipatel/Desktop/p4test/mynewfile1.txt"));
    cerr << "Test PASSED" << endl;
    return 0;
}

