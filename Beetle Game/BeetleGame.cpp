//
//  BeetleGame.cpp
//

#include "BeetleGame.h"
#include "BeetleDrawing.h"

#include <iostream>

namespace cs31
{

BeetleGame::BeetleGame() : mHuman(), mComputer(), mHumanDie(), mComputerDie()
{
    
}

// draw the board by using a BeetleDrawing to draw the two Beetles
std::string BeetleGame::display( std::string msg ) const
{
    BeetleDrawing drawing( mHuman, mComputer );
    std::string result = drawing.draw() + "\n" + msg;
    return( result );
}


// TODO when amount is zero, it is a random roll...
// otherwise, an amount value is a cheating value...
void BeetleGame::humanRoll( int amount )
{
    if (amount== 0)
    {
        mHumanDie.roll();
    }
    else
    {
        mHumanDie.setValue(amount);
    }
    // if the amount is zero, roll the Human's die
    // otherwise, cheat by forcing the amount into the Human's die
}

// TODO return the value of the Human's die
int BeetleGame::getHumanDie( ) const
{
    // for now...
    return mHumanDie.getValue();
}

// TODO convert the Human's die value to a Beetle's body part
// then depending on the body part involved, enforce the game ordering of body parts:
// - namely, body before everything else and head before eyes or antenna
// if allowed, build the desired body part on the Human's beetle
// if a body part was successfully built, return true
// otherwise, return false
bool BeetleGame::humanPlay( )
{
    int die = mHumanDie.getValue(); //number on dice that human rolls

    if (die == 1) { //Eyes only valid if there is a head
        if (mHuman.hasHead() == false)
            return false;
        else {
            if (mHuman.hasEye1() && mHuman.hasEye2())
                return false; // you can't build more eyes if both eyes are already there
            else { //one of two eyes needs to be built
                mHuman.buildEye();
                return true;
            }
        }
    }

    else if (die == 2) { //antenna is only valid if there is a head
        if (mHuman.hasHead() == false)
            return false;
        else { //head  built
            if (mHuman.hasAntenna1() && mHuman.hasAntenna2()) //both antenna are built
                return false;
            else { //at least one antenna isn't built
                mHuman.buildAntenna();
                return true;
            }
        }
    }
    
    else if (die == 3) { //legs are only if there is a body
        if (mHuman.hasBody() == false)
            return false;
        else {
            if (mHuman.hasLeg1() && mHuman.hasLeg2() && mHuman.hasLeg3() && mHuman.hasLeg4()) // legs all built
                return false;
            else { //one leg needs to be built
                mHuman.buildLeg();
                return true;
            }
        }
    }

    else if (die == 4) { //tail is only if there is a body
        if (mHuman.hasBody() == false)
            return false;
        else {
            if (mHuman.hasTail()) //has a tail, A beetle only has one tail
                return false;
            else {
                mHuman.buildTail();
                return true;
            }
        }
    }

    else if (die == 5) { //head is only if there is a body
        if (mHuman.hasBody() == false)
            return false;
        else {
            if (mHuman.hasHead() == true) //can't build multiple heads
                return false;
            else { //doesn't have head
                mHuman.buildHead();
                return true;
            }
        }
    }

    else if (die == 6) {
        if (mHuman.hasBody() == true)
            return false;
        else {
            mHuman.buildBody();
            return true;
        }
    }

    //if value is not a number between 1-6 return false because this would be invalid  input
   
    return false;
}


// TODO when amount is zero, it is a random roll...
// otherwise, an amount value is a cheating value...
void BeetleGame::computerRoll( int amount )
{
    // if the amount is zero, roll the Computer's die
    
    if (amount == 0)
    {
        mComputerDie.roll(); // create a random roll
    }
    else
    {
        mComputerDie.setValue(amount); // Set the die value to the specified amount
    }
}

// TODO return the value of the Computer's die
int BeetleGame::getComputerDie( ) const
{
    // for now...
    return mComputerDie.getValue();
}

// TODO convert the Computer's die value to a Beetle's body part
// then depending on the body part involved, enforce the game ordering of body parts:
// - namely, body before everything else and head before eyes or antenna
// if allowed, build the desired body part on the Computer's beetle
// if a body part was successfully built, return true
// otherwise, return false
bool BeetleGame::computerPlay( )
{
    int die = mComputerDie.getValue(); //number the computer rolled

    if (die == 1) { //eyes only if there is a head
        if (mComputer.hasHead() == false)
            return false;
        else {
            if (mComputer.hasEye1() && mComputer.hasEye2())
                return false; //can't build more eyes if both eyes alreayd there
            else { //one more eye needs to be built
                mComputer.buildEye();
                return true;
            }
        }
    }

    else if (die == 2) { //antenna only if there is a head
        if (mComputer.hasHead() == false)
            return false;
        else { //head is built
            if (mComputer.hasAntenna1() && mComputer.hasAntenna2()) //both antennas are built
                return false;
            else { //needs at least one more antenna
                mComputer.buildAntenna();
                return true;
            }
        }
    }

    else if (die == 3) { //legs only if there is a head
        if (mComputer.hasBody() == false)
            return false;
        else {
            if (mComputer.hasLeg1() && mComputer.hasLeg2() && mComputer.hasLeg3() && mComputer.hasLeg4()) //all legs are built
                return false;
            else { //at least one legs has to be built
                mComputer.buildLeg();
                return true;
            }
        }
    }

    else if (die == 4) { //tail isonly if there is a body
        if (mComputer.hasBody() == false)
            return false;
        else {
            if (mComputer.hasTail()) // has a tail. A beetle only has one tail
                return false;
            else {
                mComputer.buildTail();
                return true;
            }
        }
    }

    else if (die == 5) { //head is only if there is a body
        if (mComputer.hasBody() == false)
            return false;
        else {
            if (mComputer.hasHead() == true) //can't build a second head
                return false;
            else {
                mComputer.buildHead();
                return true;
            }
        }
    }

    else if (die == 6) {
        if (mComputer.hasBody() == true)
            return false;
        else {
            mComputer.buildBody();
            return true;
        }
    }


    return false;

}

    // TODO what is the current state of the game
   
BeetleGame::GameOutcome  BeetleGame::determineGameOutcome( ) const
{
    if (mComputer.isComplete() && !mHuman.isComplete()) //computer finishes board first
        return(GameOutcome::COMPUTERWONGAME);
    else if (mHuman.isComplete() && !mComputer.isComplete()) //human finishes board first
        return(GameOutcome::HUMANWONGAME);
    else
        return(GameOutcome::GAMENOTOVER); //the game still isn't over
}    
std::string  BeetleGame::stringifyGameOutcome( ) const
    {
        std::string result = "";
        switch( determineGameOutcome() )
        {
            case GameOutcome::COMPUTERWONGAME:
                result = "Computer Won!";
                break;
            case GameOutcome::HUMANWONGAME:
                result = "Human Won!";
                break;
            case GameOutcome::GAMENOTOVER:
                result = "Game Not Over!";
                break;
        }
        return( result );
    }
    
    // TODO has the game ended with a winner?
bool BeetleGame::gameIsOver() const
{
    if (mHuman.isComplete() || mComputer.isComplete())
        return true;
    else
        return false;
}

    
    
Beetle BeetleGame::getHumanBeetle( ) const
    {
        return( mHuman );
    }
Beetle BeetleGame::getComputerBeetle( ) const
    {
        return( mComputer );
    }
    
}
