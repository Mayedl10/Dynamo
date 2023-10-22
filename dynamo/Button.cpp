#include "dynamo.hpp"

Button::Button(RenderWindow* win, const char* sprite1_path, const char* sprite2_path) {
    window = win;
    textures.first = new Texture(window, sprite1_path);
    textures.second = new Texture(window, sprite2_path);
}

Button::Button(RenderWindow* win, const char* spriteSheet1, customPair<int, int> sprite1_position, customPair<int, int> sprite1_dimensions, const char* spriteSheet2, customPair<int, int> sprite2_position, customPair<int, int> sprite2_dimensions) {
    window = win;
    textures.first = new Texture(window, spriteSheet1, sprite1_position, sprite1_dimensions);
    textures.second = new Texture(window, spriteSheet2, sprite2_position, sprite2_dimensions);
}




void Button::setPosition(customPair<int, int> pos) {
    position = pos;
}

void Button::setCollisionSize(customPair<int, int> size) {
    dimensions = size;
}

void Button::setOffset(customPair<int, int> offset_) {
    displayOffset = offset_;
}

void Button::render() {
    if (textureIndex == 1) {
        textures.second->renderAt(position);
    } else {
        textures.first->renderAt(position);
    }
}

void Button::renderEx(customPair<double, double> scale, double rotationAngle) {
    if (textureIndex) {
        textures.second->renderAtEx(position, scale, rotationAngle);
    } else {
        textures.first->renderAtEx(position, scale, rotationAngle);
    }
}

bool Button::detectClick() {
    InputHandler inputHandler(window);
    auto mouseInfo = inputHandler.getMouse();
    if (mouseInfo[2]) {
        if (
        (((position.first + displayOffset.first) < (mouseInfo[0])) && ((mouseInfo[0]) < (position.first+dimensions.first + displayOffset.first)))
        &&
        (((position.second + displayOffset.second) < (mouseInfo[1])) && ((mouseInfo[1]) < (position.second+dimensions.second + displayOffset.second)))
        )
        {
            textureIndex = 1;
            return true;
        }
    }
    textureIndex = 0;
    return false;
}

Button::~Button() {
    delete textures.first;
    delete textures.second;
}
