#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// TODO

using namespace std;
template<unsigned int Win = 1, unsigned int Wout = 1>
class placeInterface : public sc_interface
{
    public:
    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;
    virtual  unsigned int testTokens() = 0;
};  

// Place Channel:
// TODO
template<unsigned int Win = 1, unsigned int Wout = 1>
class place : public placeInterface<Win, Wout>
{
    private:
    unsigned int tokens;

    public:
    place(unsigned int initial_tokens) : tokens(initial_tokens) {}

    // Implement the pure virtual functions from placeInterface
    virtual void addTokens(){
        tokens += Win;
    }

    virtual void removeTokens()  {
        //tokens -= Wout; // Note: Need to ensure that tokens never goes below zero in usage
        if (tokens >= Wout) {
            tokens -= Wout;
        } else {
            // Handle the case where tokens go below zero
            tokens = 0;
        }
    }

    virtual unsigned int testTokens()  {
        return (tokens>=Wout);
    }

};

#endif // PLACE_H
