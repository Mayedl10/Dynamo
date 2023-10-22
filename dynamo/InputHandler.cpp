#include "dynamo.hpp"

InputHandler::InputHandler(RenderWindow* win) {
    window = win;
}

bool InputHandler::detectKeyPress(int32_t keycode) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_GetScancodeFromKey(keycode)]) {
        return true;
    }

    return false;
}

std::array<int, 5> InputHandler::getMouse() {
    // returns {mouseX, mouseY, leftClick, middleClick, rightClick}
    int x, y;
    SDL_GetMouseState(&x, &y);

    float scaleX, scaleY;
    SDL_RenderGetScale(window->renderer, &scaleX, &scaleY);

    // apply scaling to get logical coordinates instead of screen coordinates
    int logicalX = static_cast<int>(x / scaleX);
    int logicalY = static_cast<int>(y / scaleY);

    const Uint32 mouseState = SDL_GetMouseState(NULL, NULL);

    std::array<int, 5> mouseInfo = {logicalX, logicalY,
                                    (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) ? 1 : 0,
                                    (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) ? 1 : 0,
                                    (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) ? 1 : 0};

    return mouseInfo;
}
