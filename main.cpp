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
    subnet s1, s2;
    SC_CTOR(toplevel) : s1("s1"),s2("s2")
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
        



        // Start a thread to trigger the transitions
        SC_THREAD(process);
    }

    void process() {
        while (true) {
            wait(10, SC_NS);
            s1.ACT.fire();  // Activate s1
            wait(10, SC_NS);
            s1.ACT.fire();  // Activate s1
            wait(10, SC_NS);
            s1.RD.fire();   // Read operation in s1
            wait(10, SC_NS);
            s1.WR.fire();   // Write operation in s1
            wait(10, SC_NS);
            s1.PRE.fire();  // Precharge s1, moving it back to IDLE
            wait(10, SC_NS);
            s1.ACT.fire();  // Similarly, activate s2
            wait(10, SC_NS);
            s2.ACT.fire();  // Similarly, activate s2
            wait(10, SC_NS);
            s2.ACT.fire();  // Similarly, activate s2
            wait(10, SC_NS);
            s2.PRE.fire();  // Precharge s1, moving it back to IDLE
            wait(10, SC_NS);
            s2.PRE.fire();  // Precharge s1, moving it back to IDLE
            wait(10, SC_NS);
            sc_stop();  // Stop the s
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
