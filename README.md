# Dynamo
## A SDL2 wrapper

### DISCLAIMER:

I do not claim to own or have written the contents of "include.zip" and "lib.zip". These files contain the current (22.10.2023) versions of the following libraries:
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf

Please extract the .zip files before usage as they are neccessary. (As you can see in the "compiling" section)




### Compiling
If you want to use this library (only distributed as source code), you need to compile it alongside your project:
- compiler flag -I:
  - "include"
  - "include/sdl"
  - "include/headers"
  - "include/SDL2"
  - "dynamo"

- compiler flag -l:
  - "mingw32"
  - "SDL2main"
  - "SDL2"
  - "SDL2_mixer"
  - "SDL2_image"
  - "SDL2_ttf"

- source files (.cpp):
  - "dynamo/*.cpp"

- other flags:
  - "-std=c++17"
  - "-Llib"

This means, for a project with `int main` in `main.cpp`, this is the compile command:<br>
```powershell
g++ -std=c++17 -Llib -o Main main.cpp dynamo/*.cpp -Iinclude -Iinclude/sdl -Iinclude/headers -Iinclude/SDL2 -Idynamo -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
```

### Using Dynamo
You need to `#include dynamo.hpp`.
You need to do `Dynamo_Init()` at the beginning.
You need to do `Dynamo_Quit()` at the very end.

### The customPair class
A struct that is used instead of std::pair

### The RenderWindow class
This class is the most important class. Think of it as an abstraction for everything that you see! It handles rendering.

Constructor parameters:
- const char* Title - Title of the window.
- customPair<int, int> dimensions - Logical size, as the window is always in fullscreen. If you want to change that, you can just change a flag in RenderWindow.cpp.

Methodes:
- load_SDL_texture<sup>[1]</sup> - loads a .png file as a SDL_Texture*.
- load_SDL_texture_from_spritesheet<sup>[1]</sup> - loads a SDL_Texture* from a spritesheet.
- clear - clears the screen
- render<sup>[1]</sup> - renders a SDL_Texture*
- renderEx<sup>[1]</sup> - like render, but with scaling and rotation support
- display - refreshes screen
- cleanup - call this at the end of your program.

### The Sound class
This class represents a sound. It can play .wav files. It is one of the only classes in dynamo that don't require a reference to a RenderWindow.

Constructor parameters:
- const char* WAV_file

Methodes:
- play - plays the sound a specified amount of times. (use -1 if you want it to play forever.) Won't work if the sound is already playing.
- stop - stops this sound's playback. Won't work if it isn't playing.
- isPlaying - returns whether the sound is currently playing.

### The Texture class
This class is a wrapper around SDL_Texture. You can use it directly and it is used internally in most other classes.

Constructor parameters (overloaded):
- Constructor 1:
  - RenderWindow* win - a pointer to your RenderWindow.
  - const char* filepath - path to a .png texture file.

- Constructor 2:
  - RenderWindow* win - a pointer to your RenderWindow.
  - const char* spriteSheetPath - path to a .png spritesheet.
  - customPair<int, int> position - position of the desired sprite on your spritesheet.
  - customPair<int, int> dimensions - width and height of the desired sprite on your spritesheet.

Methodes:
- renderAt - Renders the Texture at a position.
- renderAtEx - like renderAt, but supports scaling and rotation
- setAlpha (overloaded):
  - setAlpha 1:
    - uint8_t alpha - sets RGBA alpha channel to this value
  - setAlpha 2:
    - int base
    - int part
    - this overloaded function boils down to setAlpha 1 with the parameter being set to `static_cast<int>((static_cast<double>(part) / base) * 255)`
- setRGB - Recolours the texture.


### The Sprite class
A class that handles multiple textures, positions and movement!

Constructor Parameters:
- RenderWindow* win - a pointer to your RenderWindow.

Methodes:
- addTexture (overloaded) - adds a texture to the texture-vector. can either load an entire file or from a spritesheet.
- setTextureIndex - specifies what texture should be rendered.
- setRGB - same as Texture::setRGB
- setAlpha (overloaded) -  same as Texture::setAlpha
- setAngle - sets the rotation angle.
- setScale - specifies the scale modifier. if you do setScale({2, 0.5}), it will be twice as long on the x-axis, but 0.5 times as long on the y-axis. Don't worry, rotation doesn't mess with how scaling works.
- setOffset - a value that is added to the position before rendering.
- setVelocity - sets the velocity
- setPosition - sets the position
- move - adds the velocity to the position
- render - renders `textures[textureIndex]` at position `position+offset`, with scale `scale` and rotation `rotationAngle`.

### The Particle class
Oh boy, this thing has an overloaded constructor with A LOT of parameters. Anyways, a Particle is a texture that "decays" over time. You'll find out what "decaying" refers to later.

Constructor parameters (overloaded):
- Constructor 1:
  - RenderWindow* win - a pointer to your RenderWindow.
  - const char* textureFile - path to a png file.
  - customPair<int, int> pos - initial position of the particle.
  - customPair<double, double> initialScale - initial scale of the particle.
  - double initialRotation - initial rotation of the particle.
  - customPair<int, int> vel - initial velocity of the particle.
  - customPair<double, double> _scaleDecay - how the scale changes when calling `decay`
  - double rotationDecay - How much the rotation angle is reduced by when calling `decay` 
  - int initialTransparencyCtr - how many times you can call `decay` before the particle is invisible.

- Constructor 2:
  - It's the same as constructor 1 but loads the texture from a spritesheet.

Methodes:
  - render - renders the texture with angle `rotationAngle` and Alpha channel `static_cast<int>((static_cast<double>(transparencyCtr) / initialCtr) * 255)` at position `position`.
  - decay:
    ```cpp
    position += velocity
    scale *= scaleDecay
    rotationAngle -= rotationAngleDecay
    transparencyCtr--;
    if (transparencyCtr > 0) {
        tex->setAlpha(initialCtr, transparencyCtr);
    } else {
        tex->setAlpha(0);
    }
    ```

### The Font class
This is used to render text.

Constructor parameters:
- RenderWindow* win - a pointer to your RenderWindow.
- const char* TTF_file_path - path to your .ttf font-file.
- int size - size of the font.
- Dynamo_colour col - Dynamo_colour<sup>[2]</sup> is a wrapper around SDL_Color. This is the colour of your text.

Methodes:
- redefineFont - redefines the font class. This is useful if you want to change font size or don't want a new Font object every time you want to use a new .ttf font.
- setColour - sets the colour of the font.
- renderAt - render text at a position.
- renderAtEx - like renderAt but with support for rotation and scaling.

### The InputHandler class
This class handles keyboard and mouse input.

Constructor parameters:
- RenderWindow* win - a pointer to your RenderWindow.

Methodes:
- detectKeyPress - returns true if a certain key is pressed. Check `InputHandler.hpp` for all possible uses.<sup>[3]</sup>
- getMouse - returns an std::array<int, 5> according to the patern `{mouse_x_position, mouse_y_position, left_mouse_button_is_pressed,middle_mouse_button_is_pressed, right_mouse_button_is_pressed}`. It returns mouse coordinates according to the logical size, not screen size.


### The Button class
This is used for UI stuff.

Constructor parameters (overloaded):
- Constructor 1:
  - RenderWindow* win - a pointer to your RenderWindow.
  - const char* sprite1_path - path to a .png file that is used as the primary texture.
  - const char* sprite2_path - path to a .png file that is used as the secondary texture.

- Constructor 2:
  - It's the same as constructor 1 but loads the textures from spritesheets.

Methodes:
- setPosition<sup>[4]</sup> - sets the position of the button.
- setCollissionSize<sup>[4]</sup> - sets the "hitbox" for the button.
- setOffset<sup>[4]</sup> - sets the offset.
- render - draws the currently active texture.
- renderEx - like render, but supports scaling and rotation.
- detectClick - Returns `true` if the mouse is within the hitbox and the left mouse button is pressed, otherwise `false`. If it is pressed, the secondary texture is "activated". This means that the secondary texture is rendered instead of the primary one. Because of this, it is recommended to call this methode BEFORE `render`.

### The Clock class
This class is used for framerate regulation.

Constructor parameters:
- int targetedFramerate - the desired framerate

Methodes:
- tick - regulates FPS and returns the milliseconds since last call.

Note: The member variable `int frameCounter` is incremented every time `tick` is called. This variable gets set to 0 if it is > targetedFramerate. It is not used inside the class so it won't break anything if you try to access/modify it. Think of it as counter you can use.

### The Random class
This class could just be a namespace but I like OOP so you get it as a class.

Constructor parameters:
- None

Methodes:
- random - returns a random value from 0-1
- randint - like python's `random.randint`

# 

### Notes
[1] Internal function. You don't need to use these unless you want to work directly with SDL2.

[2] Dynamo_colour is defined like this >:)
```cpp
#define Dynamo_color SDL_Colour
#define Dynamo_colour SDL_Color
```
and SDL2 defines this:
```c
#define SDL_Colour SDL_Color
```

[3] All of the parameters for InputHandler::detectKeyPress are just redefined SDL keycodes following this pattern: `#define KEY_??? SDLK_???`. This means you can either use keycodes that start with `KEY` or codes that start with `SDLK`.

[4] This isn't part of the constructor because it has enough parameters as is.
