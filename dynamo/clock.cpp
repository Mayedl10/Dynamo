#include "clock.hpp"

Clock::Clock(int targetedFramerate) {
    frameCap = targetedFramerate;


    lastTime = SDL_GetTicks();
}

int Clock::tick() {
    // regulates fps and returns milliseconds since last call

    frameCounter++;
    if (frameCounter > frameCap) {
        frameCounter = 0;
    }

    int currentTime = SDL_GetTicks();
    int ret = lastTime;
    lastTime = SDL_GetTicks();

    if ((currentTime-ret) < 1000/frameCap) {
        SDL_Delay(1000/frameCap - (currentTime-ret));
    }

    return (currentTime-ret);
}