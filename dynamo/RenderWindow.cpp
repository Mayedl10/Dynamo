#include "dynamo.hpp"

RenderWindow::RenderWindow(const char* title, customPair<int, int> dimensions) {







    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensions.first, dimensions.second, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
        std::cerr << "RenderWindow " << title << "'s SDL_Window failed to initialize:\n" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        std::cerr << "RenderWindow " << title << "'s SDL_Renderer failed to initialize:\n" << SDL_GetError() << std::endl;
    }

    SDL_RenderSetLogicalSize(renderer, dimensions.first, dimensions.second);
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    customPair<float, float> scale = {(float)displayMode.w/(dimensions.first), (float)displayMode.h/(dimensions.second)};
    SDL_RenderSetScale(renderer, scale.first, scale.second);

    logicalSize = dimensions;
}


SDL_Texture* RenderWindow::load_SDL_texture(const char* filepath) {
    SDL_Texture* ret = nullptr;
    ret = IMG_LoadTexture(renderer, filepath);
    if (ret == nullptr) {
        std::cerr << "Failed to load texture '" << filepath << "':\n" << SDL_GetError() << std::endl;
    }
    return ret;
}

SDL_Texture* RenderWindow::load_SDL_texture_from_spritesheet(const char* filepath, customPair<int, int> position, customPair<int, int> dimensions) {
    SDL_Texture* ret = NULL;
    SDL_Surface* surface = IMG_Load(filepath);

    if (surface == NULL) {
        std::cerr << "Failed to load image '" << filepath << "': " << SDL_GetError() << std::endl;
        return NULL;
    }

    // Create a surface for the subtexture
    SDL_Surface* subSurface = SDL_CreateRGBSurface(0, dimensions.first, dimensions.second, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

    if (subSurface == NULL) {
        std::cerr << "Failed to create sub-surface for '" << filepath << "': " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return NULL;
    }

    // Copy the subtexture from the original surface to the sub-surface
    SDL_Rect srcRect = { position.first, position.second, dimensions.first, dimensions.second };
    SDL_BlitSurface(surface, &srcRect, subSurface, NULL);

    // Create a texture from the sub-surface
    ret = SDL_CreateTextureFromSurface(renderer, subSurface);

    if (ret == NULL) {
        std::cerr << "Failed to create texture from sub-surface: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(subSurface);
    SDL_FreeSurface(surface);

    return ret;
}
    
void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* tex, customPair<int, int> position) {
    SDL_Point size;
    SDL_QueryTexture(tex, NULL, NULL, &size.x, &size.y);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = size.x;
    src.h = size.y;

    SDL_Rect dst;
    dst.x = position.first;
    dst.y = position.second;
    dst.w = size.x;
    dst.h = size.y;

    if (((dst.w + position.first >= 0) && (logicalSize.first >= position.first)) && ((dst.h + position.second >= 0) && (logicalSize.second >= position.second))) {
        SDL_RenderCopy(renderer, tex, &src, &dst);
    }
}

void RenderWindow::renderEx(SDL_Texture* tex, customPair<int, int> position, customPair<double, double> scale, double rotationAngle) {
    SDL_Point size;
    SDL_QueryTexture(tex, NULL, NULL, &size.x, &size.y);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = size.x;
    src.h = size.y;

    SDL_Rect dst;
    dst.x = position.first;
    dst.y = position.second;
    dst.w = size.x * scale.first;
    dst.h = size.y * scale.second;

    if (((dst.w + position.first >= 0) && (logicalSize.first >= position.first)) && ((dst.h + position.second >= 0) && (logicalSize.second >= position.second))) {
        SDL_RenderCopyEx(renderer, tex, &src, &dst, rotationAngle, NULL, SDL_FLIP_NONE);
    }
}


void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}


void RenderWindow::cleanup() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Dynamo_Init() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cerr << "[SDL2 failed to initialize] " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cerr << "[SDL2_image failed to initialize] " << SDL_GetError() << std::endl;
    }

    if (!(Mix_Init(1))) {
        std::cerr << "[SDL2_mixer failed to initialize] " << SDL_GetError() << std::endl;
    }

    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void Dynamo_Quit() {
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}