#include "dynamo.hpp"

Sprite::Sprite(RenderWindow* win) {
    window = win;
}

void Sprite::addTexture(const char* filePath) {
    textures.push_back(new Texture(window, filePath));
}

void Sprite::addTexture(const char* spriteSheetPath, customPair<int, int> position, customPair<int, int> dimensions) {
    textures.push_back(new Texture(window, spriteSheetPath, position, dimensions));
}

void Sprite::setTextureIndex(int i) {
    textureIndex = i;
}

void Sprite::setRGB(uint8_t r, uint8_t g, uint8_t b) {
    textures[textureIndex]->setRGB(r, g, b);
}

void Sprite::setAlpha(uint8_t alpha) {
    textures[textureIndex]->setAlpha(alpha);
}

void Sprite::setAlpha(int base, int part) {
    textures[textureIndex]->setAlpha(base, part);
}

void Sprite::setAngle(double angle_) {
    angle = angle_;
}

void Sprite::setScale(customPair<double, double> scale_pair) {
    scale = scale_pair;
}

void Sprite::setOffset(customPair<int, int> offset_pair) {
    offset = offset_pair;
}

void Sprite::setVelocity(customPair<int, int> vel) {
    velocity = vel;
}

void Sprite::move() {
    position.first += velocity.first;
    position.second += velocity.second;
}

void Sprite::setPosition(customPair<int, int> pos) {
    position = pos;
}

void Sprite::render() {
    textures[textureIndex]->renderAtEx({position.first + offset.first, position.second + offset.second}, scale, angle);
}

Sprite::~Sprite() {
    for (auto p: textures) {
        delete p;
    }
}