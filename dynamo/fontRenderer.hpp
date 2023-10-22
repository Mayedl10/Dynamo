#ifndef FONTRENDERER_HPP
#define FONTRENDERER_HPP

#include "dynamo.hpp"

#define Dynamo_color SDL_Colour
#define Dynamo_colour SDL_Color

class Font {

    RenderWindow* window;
    TTF_Font* font = nullptr;

public:

    Dynamo_colour colour;

    Font(RenderWindow* win, const char* TTF_file_path, int size, Dynamo_colour col);
    void redefineFont(const char* TTF_file_path, int size);
    void setColour(Dynamo_colour col);
    void renderAt(customPair<int, int> pos, const char* message);
    void renderAtEx(customPair<int, int> pos, const char* message, customPair<double, double> scale, double rotationAngle);
    ~Font();

};

#endif