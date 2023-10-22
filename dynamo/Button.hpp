#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "dynamo.hpp"

class Button {
    RenderWindow* window;
public:
    int textureIndex = 0;
    customPair<int, int> position;
    customPair<int, int> displayOffset = {0, 0};
    customPair<int, int> dimensions;
    customPair<Texture*, Texture*> textures;

    Button(RenderWindow* win, const char* sprite1_path, const char* sprite2_path);
    Button(RenderWindow* win, const char* spriteSheet1, customPair<int, int> sprite1_position, customPair<int, int> sprite1_dimensions, const char* spriteSheet2, customPair<int, int> sprite2_position, customPair<int, int> sprite2_dimensions);

    void setPosition(customPair<int, int> pos);
    void setCollisionSize(customPair<int, int> size);
    void setOffset(customPair<int, int> offset_);
    void render();
    void renderEx(customPair<double, double> scale, double rotationAngle);
    bool detectClick();

    ~Button();

};

#endif