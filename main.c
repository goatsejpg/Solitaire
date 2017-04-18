#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core.h"
#include "card.h"
#include "solitaire.h"
#include "sleep.h"

int main(int argc, char** argv) {
	if (init() == 0) {
		printf("SDL: %s", SDL_GetError());
		quit();
		return -1;
	}

	define_cards();
	if (load_card_textures() == 0) {
		quit();
		return -1;
	}

	srand(time(NULL));

	main_loop();

	delete_card_textures();
	quit();

	return 0;
}