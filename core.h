#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>

#include "vec2.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern const int WIDTH, HEIGHT;

extern struct Vec2 mouse;

int init();
void quit();
void main_loop();

#endif // CORE_H