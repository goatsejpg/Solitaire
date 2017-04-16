#include <stdlib.h>

#include "card.h"
#include "solitaire.h"

struct Card* DECK[52];
struct Card* TABLEAUS[7][19];
struct Card* FOUNDATIONS[4][13];

// Sets everything in the deck, tableaus and 
// foundations to the null card
void init_solitaire() {
	for (unsigned char c = 0; c < 52; ++c)
		DECK[c] = &CARDS[0];

	for (unsigned char col = 0; col < 7; ++col)
		for (unsigned char row = 0; row < 19; ++row)
			TABLEAUS[col][row] = &CARDS[0];

	for (unsigned char col = 0; col < 4; ++col)
		for (unsigned char row = 0; row < 13; ++row)
			FOUNDATIONS[col][row] = &CARDS[0];
}

void shuffle_deck() {
	unsigned char temp;
	for (unsigned char c = 1; c <= 52; ++c) {
		temp = (rand() % 52) + 1;
		// If it is a null card (not set yet)
		if (DECK[temp]->Number == 0) {
			DECK[temp] = &CARDS[c];
		} 
	}
}