#ifndef DYNAMO_HPP
#define DYNAMO_HPP

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "pairs.hpp"
#include "RenderWindow.hpp"
#include "Sound.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Particle.hpp"
#include "fontRenderer.hpp"
#include "InputHandler.hpp"
#include "Button.hpp"
#include "clock.hpp"
#include "random.hpp"

void Dynamo_Init();
void Dynamo_Quit();

#endif