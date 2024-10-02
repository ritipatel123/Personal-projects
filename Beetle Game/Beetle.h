//
//  Beetle.h
//
//

#ifndef BeetleH
#define BeetleH

#include <string>

namespace cs31
{

// CS 31 Students need to complete the methods marked with TODO
class Beetle
{
public:
    
    // the possible BodyPart choices for a Beetle
    enum class BodyPart { EYE = 1, ANTENNA = 2, LEG = 3,
        TAIL = 4, HEAD = 5, BODY = 6, NOTVALID = 7 };
    
    Beetle();
    
    // convert a tossed die value into a BodyPart
    Beetle::BodyPart convertRollToBodyPart( int die ) const;
    
    // TODO build the Beetle's body
    void buildBody();
    // TODO has the Beetle's body been built?
    bool hasBody() const;
    
    // TODO build the Beetle's tail
    void buildTail();
    // TODO has the Beetle's tail been built?
    bool hasTail() const;
    
    // TODO build the Beetle's leg building leg1 before leg2 before leg3 before leg4
    void buildLeg();
    // TODO has the Beetle's legs been built?
    bool hasLeg1() const;
    bool hasLeg2() const;
    bool hasLeg3() const;
    bool hasLeg4() const;
    
    // TODO build the Beetle's head
    void buildHead();
    // TODO has the Beetle's head been built?
    bool hasHead() const;
    
    // TODO build the Beetle's eye building eye1 before eye2
    void buildEye();
    // TODO has the Beetle's eyes been built?
    bool hasEye1() const;
    bool hasEye2() const;
    
    // TODO build the Beetle's antenna building antenna1 before antenna2
    void buildAntenna();
    // TODO has the Beetle's antennas been built?
    bool hasAntenna1() const;
    bool hasAntenna2() const;
    
    // TODO is this Beetle completely built out?
    bool isComplete() const;
private:
    bool mBody, mTail, mLeg1, mLeg2, mLeg3, mLeg4, mHead, mEye1, mEye2, mAntenna1, mAntenna2;
    
};

}


#endif
