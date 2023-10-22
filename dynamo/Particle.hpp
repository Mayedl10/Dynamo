#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "dynamo.hpp"

class Particle {

    RenderWindow* window;

public:

    double rotationAngle;
    customPair<int, int> position;
    customPair<double, double> scale;
    customPair<int, int> velocity;
    customPair<int, int> accelleration;
    customPair<double, double> scaleDecay;
    double rotationAngleDecay;
    int initialCtr;
    int transparencyCtr;

    Texture* tex = nullptr;

    Particle(RenderWindow* win, const char* textureFile, customPair<int, int> pos, customPair<double, double> initialScale, double initialRotation, customPair<int, int> vel, customPair<int, int> acc, customPair<double, double> _scaleDecay, double rotationDecay, int initialTransparencyCtr);
    Particle(RenderWindow* win, const char* spriteSheetFile, customPair<int, int> spriteSheetPosition, customPair<int, int> spriteSheetSpriteDimensions, customPair<int, int> pos, customPair<double, double> initialScale, double initialRotation, customPair<int, int> vel, customPair<int, int> acc, customPair<double, double> _scaleDecay, double rotationDecay, int initialTransparencyCtr);
    void render();
    void decay();
    ~Particle();

};

#endif