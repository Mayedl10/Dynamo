#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "dynamo.hpp"

class Texture {
    RenderWindow* window;
public:
    SDL_Texture* tex;
    
    Texture(RenderWindow* win, const char* filepath);
    Texture(RenderWindow* win, const char* spriteSheetPath, customPair<int, int> position, customPair<int, int> dimensions);

    void renderAt(customPair<int, int> position);
    void renderAtEx(customPair<int, int> position, customPair<double, double> scale, double rotationAngle);
    void setAlpha(uint8_t alpha);
    void setAlpha(int base, int part);
    void setRGB(uint8_t r, uint8_t g, uint8_t b);

    ~Texture();
};

#endif