//
//  BeetleDrawing.h
//
//

#ifndef BeetleDrawingH
#define BeetleDrawingH

#include <string>
#include "Beetle.h"

namespace cs31
{


class BeetleDrawing
{
public:
    BeetleDrawing( Beetle playerBeetle, Beetle computerBeetle );
    
    // draw one line at a time
    std::string draw( int lineNumber );
    // draw all six lines
    std::string draw( );
    
private:
    Beetle mPlayer, mComputer;
};


}

#endif
