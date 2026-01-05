#ifndef Header_h
#define Header_h

#include "Arduino.h"

//Change name from "Header" when we have a proper name for this particular library:
class Header {

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