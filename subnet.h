#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"

// Subnet:
// TODO
SC_MODULE(subnet) 
{
    place<1,1> IDLE;  // Initially, the bank is in the IDLE state
    place<1,1> ACTIVE;  // Initially, no operation is ACTIVE

    // Define transitions for each operation in the memory bank
    transition<1, 1> ACT{"ACT"};
    transition<1, 1> RD{"RD"};
    transition<1, 1> WR{"WR"};
    transition<1, 1> PRE{"PRE"};

    SC_CTOR(subnet): IDLE(1), ACTIVE(0)
    {


        ACT.in.bind(IDLE);  // ACT is enabled when the bank is IDLE
        ACT.out.bind(ACTIVE);  // ACT moves the bank to ACTIVE state

        // RD transition
        RD.in.bind(ACTIVE);  // RD is enabled when the bank is ACTIVE
        RD.out.bind(ACTIVE);  // RD keeps the bank in ACTIVE state

        // WR transition
        WR.in.bind(ACTIVE);  // WR is enabled when the bank is ACTIVE
        WR.out.bind(ACTIVE);  // WR keeps the bank in ACTIVE state

        // PRE transition
        PRE.in.bind(ACTIVE);  // PRE is enabled when the bank is ACTIVE
        PRE.out.bind(IDLE);  // PRE moves the bank back to IDLE state
    }
};

#endif // SUBNET_H
