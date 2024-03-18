#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO
template<unsigned int N = 1, unsigned int M = 1, unsigned int L = 0>
SC_MODULE(transition){
    sc_port<placeInterface<>, N, SC_ALL_BOUND> in;
    sc_port<placeInterface<>, M, SC_ALL_BOUND> out;
    sc_port<placeInterface<>, L, SC_ZERO_OR_MORE_BOUND> inhibitors;  // Inhibitor places

    SC_CTOR(transition){}

    void fire(){
        for (int i = 0; i < L; ++i) {
            if (inhibitors[i]->testTokens() != 0) {
                std::cout << this->name() << ": NOT Fired (Inhibited)" << std::endl;
                return;  // Inhibited by the presence of tokens in an inhibitor place
            }
        }
        for (int i = 0; i < N; ++i) {
            if (!in[i]->testTokens()) {
                std::cout << this->name() << ": NOT Fired" << std::endl;
                return; // Do not fire if any input port does not have enough tokens
            }
        }

        // Fire the transition if all checks pass
        for (int i = 0; i < N; ++i) {
            in[i]->removeTokens(); // Consume tokens from each input port
        }
        for (int i = 0; i < M; ++i) {
            out[i]->addTokens(); // Produce tokens on each output port
        }

        std::cout << this->name() << ": Fired" << std::endl;
    
    }
};

#endif // TRANSITION_H
