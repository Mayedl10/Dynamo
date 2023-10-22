#include "dynamo.hpp"

Sound::Sound(const char* WAV_file) {
    sfxPtr = Mix_LoadWAV(WAV_file);
    if (sfxPtr == nullptr) {
        std::cerr << "Couldn't load WAV sound from file '" << WAV_file << "'." << std::endl;
    }
}

void Sound::play(int loops) {
    if (!playing) {
        playing = true;
        channel = Mix_GroupAvailable(-1);
        Mix_PlayChannel(channel, sfxPtr, loops);

    } else {
        std::cerr << "Sound already playing in channel " << std::to_string(channel) << std::endl;
    }
}

void Sound::stop() {
    if (playing) {
        playing = false;
        Mix_HaltChannel(channel);

    } else {
        std::cerr << "Can't stop sound playback because it isn't playing." << std::endl;
    }
}

bool Sound::isPlaying() {
    return playing;
}

Sound::~Sound() {
    if (sfxPtr != nullptr) {
        Mix_FreeChunk(sfxPtr);
    }
}
