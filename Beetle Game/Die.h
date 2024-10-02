//
//  Die.h
//
//

#ifndef Die_h
#define Die_h

namespace cs31
{
    

class Die
{
public:
    Die( int sides = 6 ); // by default, a six sided die
    
    // toss the Die
    void roll();
    
    // get the value of Die
    int  getValue( ) const;
    
    // cheat by forcing a value into the Die
    void setValue( int amount );
private:
    int  mSides;
    int  mValue;
};

    
}
#endif /* Die_h */
