#include "dynamo.hpp"

Particle::Particle(RenderWindow* win, const char* textureFile, customPair<int, int> pos, customPair<double, double> initialScale, double initialRotation, customPair<int, int> vel,
                    customPair<int, int> acc, customPair<double, double> _scaleDecay, double rotationDecay, int initialTransparencyCtr) {
    window = win;
    tex = new Texture(window, textureFile);
    position = pos;
    scale = initialScale;
    rotationAngle = initialRotation;
    velocity = vel;
    accelleration = acc;
    scaleDecay = _scaleDecay;
    rotationAngleDecay = rotationDecay;
    transparencyCtr = initialTransparencyCtr;
    initialCtr = initialTransparencyCtr;

}


Particle::Particle(RenderWindow* win, const char* spriteSheetFile, customPair<int, int> spriteSheetPosition, customPair<int, int> spriteSheetSpriteDimensions,
                    customPair<int, int> pos, customPair<double, double> initialScale, double initialRotation, customPair<int, int> vel, customPair<int, int> acc,
                    customPair<double, double> _scaleDecay, double rotationDecay, int initialTransparencyCtr) {
    window = win;

    tex = new Texture(window, spriteSheetFile, spriteSheetPosition, spriteSheetSpriteDimensions);

    position = pos;
    scale = initialScale;
    rotationAngle = initialRotation;
    velocity = vel;
    accelleration = acc;
    scaleDecay = _scaleDecay;
    rotationAngleDecay = rotationDecay;
    transparencyCtr = initialTransparencyCtr;
    initialCtr = initialTransparencyCtr;
}


void Particle::render() {
    tex->renderAtEx(position, scale, rotationAngle);
}


void Particle::decay() {
    position.first += velocity.first;
    position.second += velocity.second;

    scale.first *= scaleDecay.first;
    scale.second *= scaleDecay.second;

    rotationAngle -= rotationAngleDecay;

    velocity.first += accelleration.first;
    velocity.second += accelleration.second;


    transparencyCtr--;
    if (transparencyCtr > 0) {
        tex->setAlpha(initialCtr, transparencyCtr);
    } else {
        tex->setAlpha(0);
    }
    

}


Particle::~Particle() {
    delete tex;
}

