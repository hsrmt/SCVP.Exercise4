#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO
template<unsigned int N = 1, unsigned int M = 1>
SC_MODULE(transition){
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;

    SC_CTOR(transition){}

    void fire(){
        for(int i = 0; i < N; ++i) {
            if (in[i]->testTokens() == 0) {
                std::cout <<this->name() << ": NOT Fired " << std::endl;
                return; // If any input port does not have a token, do not fire
            }
        }

        // If all input ports have tokens, fire the transition
        for(int i = 0; i < N; ++i) {
            in[i]->removeTokens(1); // Consume one token from each input port
        }
        for(int i = 0; i < M; ++i) {
            out[i]->addTokens(1); // Produce one token on each output port
        }

        // Announce that the transition has fired
        std::cout << this->name() << ": Fired" << std::endl;
    
    }
};

#endif // TRANSITION_H
