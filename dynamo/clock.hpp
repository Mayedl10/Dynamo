#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "dynamo.hpp"

class Clock {
    int lastTime;
public:
    int frameCounter = 0;
    int frameCap = 60;
    Clock(int targetedFramerate);
    int tick();
};

#endif