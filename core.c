#include <SDL2/SDL.h>
#include <stdio.h>

#include "vec2.h"
#include "sleep.h"
#include "core.h"
#include "solitaire.h"

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event event;

const int WIDTH = 800, HEIGHT = 600;

struct Vec2 mouse;
struct Vec2 mouse_start;
SDL_Texture* background;

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
	SDL_DestroyTexture(background);
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if (window != NULL)
		SDL_DestroyWindow(window);
	SDL_Quit();
}

int check_collision_point(SDL_Rect* hitbox, struct Vec2* point) {
	return (hitbox->x <= point->x) && (hitbox->y <= point->y) 
		&& (hitbox->x + hitbox->w >= point->x) 
		&& (hitbox->y + hitbox->h >= point->y) ? 1 : 0;
}

int check_collision_rect(SDL_Rect* a, SDL_Rect* b) {
	return (abs(a->x - b->x) * 2 < (a->w + b->w)) && 
		(abs(a->y - b->y) * 2 < (a->h + b->h)) ? 1 : 0;
}

void main_loop() {
	char playing = 1;
	char mouse_left_down = 0;
	char draw_frame = 1;

	enum SECTION_CLICKED s_clicked;

	init_solitaire();
	shuffle_deck();

	setup_tableaus();
	update_sizes();
	update_hitboxes();

	while (playing) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				playing = 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_GetMouseState(&mouse_start.x, 
						&mouse_start.y);
					mouse = mouse_start;
					mouse_left_down = 1;
					s_clicked = check_section_clicked();
					switch (s_clicked) {
					case __TABLEAU:
						break;
					case __DECK:
						draw_card();
						draw_frame = 1;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					mouse_left_down = 0;
					if (tableau_picked_up) {
						tableau_picked_up = 0;
						unsigned char I = 
							check_tableau_dragged_to(
								TABLEAUS[
								tableau_picked_up_root.x][
								tableau_picked_up_root.y]
							);
						if (I != 8) {
							append_tableau_onto_tableau(I,
							tableau_picked_up_root);
						}
						uncover_top_hidden_cards();
					}
					if (drawn_picked_up) {
						drawn_picked_up = 0;
						unsigned char I =
							check_tableau_dragged_to(
								DRAWN[DRAWN_SIZE-1]);
						printf("%d\n", I);
						if (I != 8) {
							append_card_onto_tableau(I, 
								DRAWN[DRAWN_SIZE-1]);
							--DRAWN_SIZE;
						}
						uncover_top_hidden_cards();
					}
					draw_frame = 1;
				}
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					draw_frame = 1;
				}
				break;
			}
		}

		if (mouse_left_down) {
			SDL_GetMouseState(&mouse.x, &mouse.y);
			draw_frame = 1;
		}
		if (draw_frame) {
			render_table();
			SDL_RenderPresent(renderer);
			draw_frame = 0;
		}
		_sleep(25);
	}
}