#include "dynamo.hpp"

Texture::Texture(RenderWindow* win, const char* filepath) {
    window = win;
    tex = window->load_SDL_texture(filepath);
}

Texture::Texture(RenderWindow* win, const char* spriteSheetPath, customPair<int, int> position, customPair<int, int> dimensions) {
    window = win;
    tex = window->load_SDL_texture_from_spritesheet(spriteSheetPath, position, dimensions);
}

void Texture::renderAt(customPair<int, int> position) {
    window->render(tex, position);
}

void Texture::renderAtEx(customPair<int, int> position, customPair<double, double> scale, double rotationAngle) {
    window->renderEx(tex, position, scale, rotationAngle);
}

void Texture::setAlpha(uint8_t alpha) {
    SDL_SetTextureAlphaMod(tex, alpha);
}

void Texture::setAlpha(int base, int part) {
    SDL_SetTextureAlphaMod(tex, static_cast<int>((static_cast<double>(part) / base) * 255));
}

void Texture::setRGB(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(tex, r, g, b);
}

Texture::~Texture() {
    SDL_DestroyTexture(tex);
    tex = nullptr;
}