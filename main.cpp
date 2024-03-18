#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO
SC_MODULE(toplevel) {
 place p1, p2;
    transition t1, t2;

    SC_CTOR(toplevel)
        // Initialize places with initial token counts and transitions with their names
        : p1(1) // Let's assume p1 starts with 1 token
        , p2(0) // and p2 starts with 0 tokens
        , t1("t1")
        , t2("t2")
    {
        // Bind the ports of the transitions to the places
        t1.in(p1);
        t1.out(p2);
        t2.in(p2);
        t2.out(p1);

        // Start a thread to trigger the transitions
        SC_THREAD(process);
    }

    void process() {
        while (true) {
            wait(10, SC_NS);
            t1.fire();
            wait(10, SC_NS);
            t1.fire();
            wait(10, SC_NS);
            t2.fire();
            sc_stop(); // Stop the simulation
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
