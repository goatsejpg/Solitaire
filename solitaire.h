#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include <SDL2/SDL.h>

#include "vec2.h"
#include "card.h"

extern struct Card* DECK[52];
extern struct Card* TABLEAUS[7][19];
extern struct Card* FOUNDATIONS[4][13];
extern struct Card* DRAWN[52];

extern unsigned char DECK_SIZE;
extern unsigned char DRAWN_SIZE; 
extern unsigned char FOUNDATIONS_SIZE[4];
extern unsigned char TABLEAUS_SIZE[7];

extern SDL_Rect deck_hitbox;
extern SDL_Rect drawn_hitbox;

extern char tableau_picked_up;
extern char drawn_picked_up;
extern struct Vec2 tableau_picked_up_root;
extern SDL_Rect picked_up_hitbox;

void init_solitaire();
void shuffle_deck();
void setup_tableaus();
void render_table();
void update_hitboxes();
void update_sizes();
int check_win();
void draw_card();
// Returns 8 if dragged card is not on a tableau / can't be legally placed
unsigned char check_tableau_dragged_to(struct Card* card);
void append_tableau_onto_tableau(unsigned char tableau, struct Vec2 root);
void append_card_onto_tableau(unsigned char tableau, struct Card* card);
void uncover_top_hidden_cards();

void restart_game();

enum SECTION_CLICKED {__DECK, __TABLEAU, __FOUNDATION, __DRAWN, __NULL};
enum SECTION_CLICKED check_section_clicked();
extern unsigned char __FOUNDATION_CLICKED;

#endif // SOLITAIRE_H