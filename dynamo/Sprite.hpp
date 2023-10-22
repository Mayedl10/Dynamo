#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "dynamo.hpp"

class Sprite {
    RenderWindow* window;

public:
    std::vector<Texture*> textures;
    int textureIndex = 0;
    customPair<int, int> position;
    customPair<int, int> offset;
    customPair<double, double> scale = {1, 1};
    double angle;

    customPair<int, int> velocity;

    Sprite(RenderWindow* win);

    void addTexture(const char* filePath);
    void addTexture(const char* spriteSheetPath, customPair<int, int> position, customPair<int, int> dimensions);
    void setTextureIndex(int i);
    void setRGB(uint8_t r, uint8_t g, uint8_t b);
    void setAlpha(uint8_t alpha);
    void setAlpha(int base, int part);
    void setAngle(double angle_);
    void setScale(customPair<double, double> scale_pair);
    void setOffset(customPair<int, int> offset_pair);
    void setVelocity(customPair<int, int> vel);
    void setPosition(customPair<int, int> pos);
    void move();
    void render();

    ~Sprite();

};

#endif