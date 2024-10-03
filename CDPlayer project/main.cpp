#include <iostream>
#include <string>
#include <cctype>
using namespace std;
bool isValidCDPlayerString(string cdstring);
bool isOpen(string cdstring);
bool hasCD(string cdstring);
int totalTracksPlayed(string cdstring);
int currentTrack(string cdstring);
int total = 0;


int main() {
    string cdstring;
    
    int x = 0;
    
    cout.setf( ios::boolalpha ); // prints bool values as "true" or "false"
    
    while(x < 25) {
        cout << "Enter a CD String: ";
        getline(cin, cdstring);
        cout << "isValidCDPlayerString: " << isValidCDPlayerString(cdstring) << endl;
        cout<<"isOpen: " <<isOpen(cdstring)<< endl;
        cout<<"hasCD: "<<hasCD(cdstring)<<endl;
        cout<<"totalTracksPlayed: "<<totalTracksPlayed(cdstring) << endl;
        cout<<"currentTrack: "<<currentTrack(cdstring)<<endl;
        x++;
    }
    
    return 0;
}
    
bool isValidCDPlayerString(string cdstring) {
    bool isOpened = false;
    bool isInserted = false;
    bool isClosed = false;
    bool isStopped = false;
    bool isPlaying = false;
    bool isRemoved = false;
    int lastTrack = 0;
    
    if (cdstring.empty() || cdstring.at(0) != 'O') {
        return false;
    }
    
    for (char x : cdstring) {
        switch (x) {
            case 'O':
                if (isOpened) {
                    return false;
                }
                isOpened = true;
                isClosed = false;
                break;
                //O comes first and can only occur again if the player is initially closed (C)
            case 'I':
                if (!isOpened || isInserted) {
                    return false;
                }
                isInserted = true;
                break;
                //I can only go after O if there is not a cd currently in the player
            case 'R':
                if (!isOpened || !isInserted) {
                    return false;
                }
                isRemoved = true;
                isInserted = false;
                isPlaying = false;
                lastTrack = 0;
                break;
                //R can only happen after I is already stated
            case 'C':
                if (!isOpened) {
                    return false;
                }
                isOpened = false;
                isClosed = true;
                break;
                //C can only occur if the player is currently open (O)
            case 'P':
                if (!isInserted || isOpened) {//Does it have to be closed to be playing?
                    return false;
                }
                isPlaying = true;
                isRemoved = false;
                isStopped = false;
                break;
                //P can only occur if O and I and C have already occured
            case 'S':
                if (!isInserted || !isPlaying) {
                    return false;
                }
                isStopped = true;
                isPlaying = false;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                if(isRemoved || isOpened || isStopped)
                    return false;
                
                int trackNumber = x - '0';
                int difference = trackNumber - lastTrack; //this should always be exactly 1
                if(trackNumber <= lastTrack || difference != 1)
                    return false;
                else
                    lastTrack = trackNumber;
                break;
            }
            default: //letters that are not acceptable
                return false;
                
        }//make default about the extra characters and write cases for each number
    }
    
    return true;
}

//make a new function that cuts the strings up into pieces (a substring)




bool isOpen(string cdstring){
    if (!isValidCDPlayerString (cdstring))
        return false;
    bool isOpen = false;
    for(char x: cdstring){
        if(x == 'O'){
            isOpen = true;
        }
        else if (x =='C'){
            isOpen = false;
        }
    }
    return isOpen;
}


bool hasCD(string cdstring) {
    if (!isValidCDPlayerString (cdstring))
        return false;
    
    bool inserted = false;
    for (size_t x = 0; x < cdstring.length(); x++) {
        if (cdstring.at(x) == 'I'){
            inserted = true;
        }
        else if (cdstring.at(x) == 'R'){
            inserted = false;
        }
    }
    return inserted;
    //used to evaluate if the cdstring has I in it, indicating a CD is in the player
}



int totalTracksPlayed(string cdstring){
    if (!isValidCDPlayerString (cdstring)){
        return -1;
    }
    int totalTracks = 0;
    for (char x : cdstring) {
        if (x >= '1' && x <='9') {
            totalTracks++; // If track is played then you increment the track value by 1
        }
    }
    
    return totalTracks;
}

int currentTrack(string cdstring) {
    if(!isValidCDPlayerString (cdstring)){
        return -1;
    }
    
    //bool trackingAmount = false;
    int trackNum = 0;
    bool isNumber = false;
    bool isInserted = false;
    
    for(char x : cdstring) {
        if (x == 'I'){
            isInserted = true;
            trackNum = 0;
            //trackingAmount=false;
        }
        
        else if (x =='R') {
            isInserted = false;
        }
        
        else if (isInserted && x >= '1' && x<='9') {
            isNumber = true;
            int currentTrack = x - '0';
            trackNum = currentTrack + 1;
        }
    }
    
    if(isInserted == true && isNumber == true)
        return trackNum;
    else if(isInserted == true && isNumber == false)
        return 1;
    else
        return -1;
}

//Problems: STRING, WHAT THEY SHOULD BE
//OICP123SOCP456S = TRUE
//OICP123SOCP456S= true
//OIR123 -- issues
//OICP123O= 4 and true
//OICPP what is the answer
//OICP123P= true
//OIRIC= TRUE
//OICPS= true
//OICP123SO=TRUE
//OICP123OS=true
//OICP123OS= TRUE
// O= -1
//OIC
//OICP
//OICP1
