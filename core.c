#include <SDL2/SDL.h>
#include <stdio.h>

#include "vec2.h"
#include "sleep.h"
#include "core.h"

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event event;

const int WIDTH = 800, HEIGHT = 600;

struct Vec2 mouse;

int init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 0;
	else
		printf("SDL: Video initalized.\n");

	window = SDL_CreateWindow("Solitaire", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) 
		return 0;
	else
		printf("SDL: Window created.\n");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Falling back to software renderer\n");
		renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_SOFTWARE); // Software fallback.
		if (renderer == NULL) {
			return 0;
		} else {
			printf("SDL: Software renderer created.\n");
		}
	} else {
		printf("SDL: Accelerated renderer created.\n");
	}
}

void quit() {
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if (window != NULL)
		SDL_DestroyWindow(window);
	SDL_Quit();
}

void main_loop() {
	char playing = 1;
	char mouse_left_down = 0;
	char draw_frame = 0;

	while (playing) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				playing = 0;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					mouse_left_down = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_RIGHT)
					mouse_left_down = 0;
				break;
			}
		}

		if (mouse_left_down)
			SDL_GetMouseState(&mouse.x, &mouse.y);

		_sleep(17);
	}
}