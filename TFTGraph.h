#ifndef TFTGraph_h
#define TFTGraph_h

#include "Arduino.h"

class TFTGraph {

    //This is all just a bunch of junk variables that don't mean anything:a
    public:
        Morse(int pin);
        void begin();
        void dot();
        void dash();
    private:
        int _pin;
}

#endif