#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO
SC_MODULE(transition){
    sc_port<placeInterface> in;
    sc_port<placeInterface> out;

    SC_CTOR(transition){}

    void fire(){
        if (in->testTokens() > 0) {
            // Transition fires
            in->removeTokens(1); // Remove one token from the input place
            out->addTokens(1); // Add one token to the output place
            std::cout << this->name() << ": Fired" << std::endl;
        } else if(in->testTokens() == 0) {
            // Transition does not fire due to lack of tokens
            std::cout << this->name() << ": NOT Fired" << std::endl;
        }
    }

};

#endif // TRANSITION_H
