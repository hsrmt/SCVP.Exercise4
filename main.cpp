#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO
SC_MODULE(toplevel) {
    // place<1,1> p1, p2, p3, p4;
    // transition<1, 2> t1; 
    // transition<2, 1> t2{"t2"}; 
    // transition<1, 1> t3{"t3"}; // t3 has one input and one output
    place<1,1> IDLE;  // Initially, the bank is in the IDLE state
    place<1,1> ACTIVE;  // Initially, no operation is ACTIVE

    // Define transitions for each operation in the memory bank
    transition<1, 1> ACT{"ACT"};
    transition<1, 1> RD{"RD"};
    transition<1, 1> WR{"WR"};
    transition<1, 1> PRE{"PRE"};
    SC_CTOR(toplevel) : IDLE(1), ACTIVE(0)
    {
        // Bind the ports of the transitions to the places
        // act.in.bind(p1);
        // t1.out.bind(p2);
        // t1.out.bind(p3);        
        // t2.in.bind(p2);
        // t2.in.bind(p4);
        // t2.out.bind(p1);
        // t3.in.bind(p3);
        // t3.out.bind(p4);   
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



        // Start a thread to trigger the transitions
        SC_THREAD(process);
    }

    void process() {
        while (true) {
            wait(10, SC_NS);
            ACT.fire();
            wait(10, SC_NS);
            ACT.fire();
            wait(10, SC_NS);
            RD.fire();
            wait(10, SC_NS);
            WR.fire();
            wait(10, SC_NS);
            PRE.fire();
            wait(10, SC_NS);
            ACT.fire();
            sc_stop(); 
        }
    }
};
int sc_main(int, char**)
{
    // TODO
    toplevel t("t");
    sc_start();
    return 0;
}
