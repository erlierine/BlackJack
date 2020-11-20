#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>


#define MSG_LENGTH 200
#define MAX_PATH_LEN 100
#define LINE_LENGTH 256
#define MAX_LINES 32
#define MAX_HAND_SIZE 12
#define NUM_OF_CARDS 15
#define BUFFSIZE 64
#define DECK_SIZE 52

#define BAR "________________________________________________________________________________\n"

enum card_type
{
    C_ACE = 11,
    C_2 = 2,
    C_3 = 3,
    C_4 = 4,
    C_5 = 5,
    C_6 = 6,
    C_7 = 7,
    C_8 = 8,
    C_9 = 9,
    C_10 = 10,
    C_JACK = 12,
    C_QUEEN = 13,
    C_KING = 14
};

typedef struct Card
{
    enum card_type type;
    char image_path[MAX_PATH_LEN];
} card;

typedef struct Deck
{
    card* cards[DECK_SIZE];
    unsigned next_card;
} deck;

typedef struct Hand
{
    card* cards[DECK_SIZE];
    unsigned size;
} hand;

void error(char* msg, int exit_code);
void hit(hand *h, deck* d);
int hand_value(hand* h);
void show_hand(hand *h, char *caption);
void check_card(card card);
void init_cards(card* cards, char* map_path);
void shuffle(deck* d, unsigned* seed);
deck new_deck(card* cards, unsigned *seed);
void start_game(hand* dealer, hand *player, deck* d);


#endif // BLACKJACK_H
