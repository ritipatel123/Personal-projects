//
//  BeetleDrawing.cpp
//
//

#include "BeetleDrawing.h"
#include <string>


namespace cs31
{


BeetleDrawing::BeetleDrawing( Beetle playerBeetle, Beetle computerBeetle )
{
    mPlayer = playerBeetle;
    mComputer = computerBeetle;
}

// draw one line at a time
std::string BeetleDrawing::draw( int lineNumber )
{
    using namespace std;
    string s = "";
    switch( lineNumber )
    {
        case 0:
            s += "    Human Beetle        Computer Beetle";
            break;
        case 1:
            if (mPlayer.hasAntenna1())
            {
                s += "Antenna   ";
            }
            else
            {
                s += "          ";
            }
            if (mPlayer.hasAntenna2())
            {
                s += "Antenna";
            }
            else
            {
                s += "       ";
            }
            s += "             ";
            if (mComputer.hasAntenna1())
            {
                s += "Antenna   ";
            }
            else
            {
                s += "          ";
            }
            if (mComputer.hasAntenna2())
            {
                s += "Antenna";
            }
            break;
        case 2:
            if (mPlayer.hasEye1())
            {
                s += "    Eye";
            }
            else
            {
                s += "       ";
            }
            if (mPlayer.hasEye2())
            {
                s += " - Eye";
            }
            else
            {
                s += "      ";
            }
            s += "             ";
            if (mComputer.hasEye1())
            {
                s += "        Eye";
            }
            else
            {
                s += "           ";
            }
            if (mComputer.hasEye2())
            {
                s += " - Eye";
            }
            break;
        case 3:
            if (mPlayer.hasHead())
            {
                s += "        Head";
            }
            else
            {
                s += "            ";
            }
            s += "                ";
            if (mComputer.hasHead())
            {
                s += "       Head";
            }
            break;
        case 4:
            if (mPlayer.hasLeg1())
            {
                s += "Leg - ";
            }
            else
            {
                s += "      ";
            }
            if (mPlayer.hasBody())
            {
                s += "  Body";
            }
            else
            {
                s += "      ";
            }
            if (mPlayer.hasLeg3())
            {
                s += " - Leg";
            }
            else
            {
                s += "      ";
            }
            s += "       ";
            if (mComputer.hasLeg1())
            {
                s += "    Leg - ";
            }
            else
            {
                s += "          ";
            }
            if (mComputer.hasBody())
            {
                s += "Body";
            }
            if (mComputer.hasLeg3())
            {
                s += " - Leg";
            }
            break;
        case 5:
            if (mPlayer.hasLeg2())
            {
                s += "Leg - ";
            }
            else
            {
                s += "      ";
            }
            if (mPlayer.hasBody())
            {
                s += "  Body";
            }
            else
            {
                s += "      ";
            }
            if (mPlayer.hasLeg4())
            {
                s += " - Leg";
            }
            else
            {
                s += "      ";
            }
            s += "       ";
            if (mComputer.hasLeg2())
            {
                s += "    Leg - ";
            }
            else
            {
                s += "          ";
            }
            if (mComputer.hasBody())
            {
                s += "Body";
            }
            if (mComputer.hasLeg4())
            {
                s += " - Leg";
            }
            break;
        case 6:
            if (mPlayer.hasTail())
            {
                s += "        Tail";
            }
            else
            {
                s += "            ";
            }
            s += "                ";
            if (mComputer.hasTail())
            {
                s += "       Tail";
            }
            break;

        default:
            break;
    }
    return( s );
}
// draw all six lines
std::string BeetleDrawing::draw( )
{
    using namespace std;
    string result = "";
    for (int i = 0; i <= 6; i++)
    {
        result += "\n" + draw( i );
    }
    result += "\n";
    return( result );
}


}


