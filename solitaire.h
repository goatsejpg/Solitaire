#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include "card.h"

extern struct Card* DECK[52];
extern struct Card* TABLEAUS[7][19];
extern struct Card* FOUNDATIONS[4][13];

void init_solitaire();
void shuffle_deck();

#endif // SOLITAIRE_H