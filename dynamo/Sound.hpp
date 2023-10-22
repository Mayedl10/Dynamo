#ifndef SOUND_HPP
#define SOUND_HPP

#include "dynamo.hpp"

class Sound {

    Mix_Chunk* sfxPtr;
    int channel = -1;
    bool playing;

public:

    Sound(const char* WAV_file);
    void play(int loops);
    void stop();
    bool isPlaying();
    ~Sound();

};

#endif