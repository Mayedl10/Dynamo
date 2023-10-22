#include "dynamo.hpp"

Font::Font(RenderWindow* win, const char* TTF_file_path, int size, Dynamo_colour col) {
    window = win;
    font = TTF_OpenFont(TTF_file_path, size);
    colour = col;
}

void Font::redefineFont(const char* TTF_file_path, int size) {
    font = TTF_OpenFont(TTF_file_path, size);
    
}

void Font::setColour(Dynamo_colour col) {
    colour = col;
}

void Font::renderAt(customPair<int, int> pos, const char* message) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    window->render(texture, {pos.first, pos.second});
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Font::renderAtEx(customPair<int, int> pos, const char* message, customPair<double, double> scale, double rotationAngle) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    window->renderEx(texture, {pos.first, pos.second}, scale, rotationAngle);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

Font::~Font() {
    TTF_CloseFont(font);
}