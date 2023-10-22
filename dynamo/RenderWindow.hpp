#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include "dynamo.hpp"

class RenderWindow {
    SDL_Window* window = nullptr;
public:
    SDL_Renderer* renderer = nullptr;

    customPair<int, int> logicalSize;

    RenderWindow(const char* title, customPair<int, int> dimensions);
    SDL_Texture* load_SDL_texture(const char* filepath);
    SDL_Texture* load_SDL_texture_from_spritesheet(const char* filepath, customPair<int, int> position, customPair<int, int> dimensions);
    void clear();
    void render(SDL_Texture* tex, customPair<int, int> position);
    void renderEx(SDL_Texture* tex, customPair<int, int> position, customPair<double, double> scale, double rotationAngle);
    void display();

    void cleanup();
};

#endif