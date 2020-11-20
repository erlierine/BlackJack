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

void error(char* msg, int exit_code)
{
    printf ("%s\n", msg);
    exit(exit_code);
}

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

void hit(hand *h, deck* d)
{
    h->cards[h->size] = d->cards[d->next_card++];
    h->size++;
}

int hand_value(hand* h)
{
    int i;
    int value = 0;

    int has_ace = 0;
    for(i=0;i<h->size;i++)
    {
        enum card_type type = h->cards[i]->type;
        switch (type)
        {
            case C_2:
                value += 2;
                break;
            case C_3:
                value += 3;
                break;
            case C_4:
                value += 4;
                break;
            case C_5:
                value += 5;
                break;
            case C_6:
                value += 6;
                break;
            case C_7:
                value += 7;
                break;
            case C_8:
                value += 8;
                break;
            case C_9:
                value += 9;
                break;
            case C_10:
                value += 10;
                break;
            case C_ACE:
                value += 1;
                has_ace += 1;
                break;
            case C_JACK:
            case C_QUEEN:
            case C_KING:
                value += 10;
                break;
        }
    }

    if(has_ace && value <= 11)
        value += 10;

    return value;
}

void show_hand(hand *h, char *caption)
{
    printf("%s\n\n", caption);
    printf (BAR);
    unsigned i;

    char **lines = malloc(MAX_LINES * sizeof (char*));
    int size = 0;
    for(i=0;i<MAX_LINES;i++)
    {
        lines[i] = malloc (LINE_LENGTH);
        int j;
        for(j=0;j<LINE_LENGTH;j++)
            lines[i][j] = '\0';
    }


    for(i=0;i<h->size;i++)
    {
        FILE* f = fopen(h->cards[i]->image_path, "r");
        if(f == NULL)
            error("Reading card image failed!", 1);
        char* line = malloc(LINE_LENGTH);
        int line_index = 0;

        while(fgets(line, LINE_LENGTH, f) != NULL)
        {
            if(strlen(lines[line_index]) > 0)
                sprintf (lines[line_index], "%s %s", lines[line_index], line);
            else
                strcpy (lines[line_index], line);
            int n = strlen(lines[line_index]);
            if(lines[line_index][n-1] == '\n')
                lines[line_index][n-1] = '\0';
            line_index++;

            size = (line_index > size) ? line_index : size;
        }
        free(line);
        fclose (f);
    }

    for(i=0;i<size;i++)
        printf("%s\n", lines[i]);

    for(i=0;i<MAX_LINES;i++)
        free(lines[i]);
    free(lines);

    printf("score:%d\n\n", hand_value (h));
    printf (BAR);
}


void make_cards() {
    int i;
    FILE *f;
    for(i=2;i<10;i++)
    {
        char file_path[MAX_PATH_LEN];
        sprintf (file_path, "cards/%d.txt", i);
        f = fopen(file_path, "w");
        fprintf(f, "*********\n");
        fprintf(f, "*       *\n");
        fprintf(f, "*       *\n");
        fprintf(f, "*   %d   *\n", i);
        fprintf(f, "*       *\n");
        fprintf(f, "*       *\n");
        fprintf(f, "*********\n");
        fclose (f);
    }

    f = fopen("cards/10.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*  10   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/ace.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   A   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/jack.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   J   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/queen.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   Q   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/king.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   K   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose(f);

    return;
}

void check_card(card card)
{
    FILE* f = fopen(card.image_path, "r");
    if(f == NULL)
        error ("Reading cards image failed!", 1);

    char* line = malloc(LINE_LENGTH * sizeof (char));
    while (fgets(line, LINE_LENGTH, f) != NULL)
    {
        int line_len = strlen(line);
        if(line_len >= 70)
            error ("[ERR] Invalid File(s).", -3);
    }

    free(line);
    fclose (f);
}

void init_cards(card* cards, char* map_path)
{
    struct stat file_info;

    if(stat(map_path, &file_info) == -1)
    {
        error ("Reading file info failed.", 1);
    }
    if(!S_ISDIR (file_info.st_mode))
    {
        error ("Map path does not point on a directory.", 1);
    }

    DIR* dir = opendir(map_path);
    struct dirent* entry = NULL;

    int found_card[NUM_OF_CARDS];
    int i;
    for(i=0; i<NUM_OF_CARDS; i++)
    {
        found_card[i] = 0;
    }

    while((entry = readdir(dir)) != NULL)
    {
        int card_index = -1;
        char* name = entry->d_name;
        if(strcmp (name, "2.txt") == 0)
            card_index = C_2;
        else if(strcmp (name, "3.txt") == 0)
            card_index = C_3;
        else if(strcmp (name, "4.txt") == 0)
            card_index = C_4;
        else if(strcmp (name, "5.txt") == 0)
            card_index = C_5;
        else if(strcmp (name, "6.txt") == 0)
            card_index = C_6;
        else if(strcmp (name, "7.txt") == 0)
            card_index = C_7;
        else if(strcmp (name, "8.txt") == 0)
            card_index = C_8;
        else if(strcmp (name, "9.txt") == 0)
            card_index = C_9;
        else if(strcmp (name, "10.txt") == 0)
            card_index = C_10;
        else if(strcmp (name, "ace.txt") == 0)
            card_index = C_ACE;
        else if(strcmp (name, "jack.txt") == 0)
            card_index = C_JACK;
        else if(strcmp (name, "queen.txt") == 0)
            card_index = C_QUEEN;
        else if(strcmp (name, "king.txt") == 0)
            card_index = C_KING;

        if(card_index == -1)
            continue;
        found_card[card_index] = 1;
        sprintf (cards[card_index].image_path, "./%s/%s", map_path, name);
        cards[card_index].type = card_index;
    }

    closedir (dir);

    for(i=2;i<NUM_OF_CARDS;i++)
    {
        if(found_card[i] == 0)
            error ("Missing a card from map path!", 1);
    }
    for(i=2;i<NUM_OF_CARDS;i++)
    {
        check_card(cards[i]);
    }
}

void shuffle(deck* d, unsigned* seed)
{
    if(seed)
        srand (*seed);
    else
        srand (time(NULL));
    int i;
    for(i=DECK_SIZE-1; i>=1; i--)
    {
        int j = ((unsigned)rand()) % (i+1);
        card *t = d->cards[i];
        d->cards[i] = d->cards[j];
        d->cards[j] = t;
    }

}

deck new_deck(card* cards, unsigned *seed)
{
    deck d;
    d.next_card = 0;
    int i;
    for(i=0;i<DECK_SIZE;i++){
        d.cards[i] = &cards[(i+8)/4];
    }
    shuffle(&d, seed);
    return d;
}

void start_game(hand* dealer, hand *player, deck* d)
{
    player->size = 0;
    dealer->size = 0;

    hit(player, d);
    hit(player, d);

    hit(dealer, d);
    hit(dealer, d);
    dealer->size--;

    show_hand (player, "YOUR CARDS:");
    show_hand (dealer, "DEALERS CARDS:");
}

int main(int argc, char** argv)
{
//    make_cards ();
    if(argc <2)
    {
        // First way of processing command line args
        // printf("usage: %s <input_folder>\n", argv[0]);
        // error(EXIT_FAILURE);

        // Second way is by calling our error func
        // char error_msg[MSG_LENGTH];
        // strcpy(error_msg, "usage: ");
        // strcat(strcat(error_msg , argv[0]),  "<input_folder>\n");
        // error(error_msg, EXIT_FAILURE

        // Third, easiest way
        char *error_msg = (char*)malloc (MSG_LENGTH * sizeof (char));
        sprintf (error_msg, "usage: %s <input_folder>\n", argv[0]);
        error(error_msg, EXIT_FAILURE);
        if(error_msg != NULL)
        {
            free(error_msg);
        }
    }

    char* map_path = argv[1];
    unsigned* seed = NULL;
    if(argc >= 3) {
        unsigned seed_value = strtol (argv[2], NULL, 10);
        seed = &seed_value;
    }

    card* cards = malloc(NUM_OF_CARDS * sizeof (card));
    init_cards (cards, map_path);

    deck d = new_deck (cards, seed);
    hand dealer;
    hand player;

    start_game(&dealer, &player, &d);

    int player_has_blackjack = hand_value (&player) == 21;
    if(player_has_blackjack)
    {
        dealer.size++;
        int dealer_has_blackjack = hand_value (&dealer) == 21;
        show_hand(&dealer, "BLACKJACK! DEALER'S CARDS:");

        if(!dealer_has_blackjack)
            printf("YOU WIN! :)\n");
        else
            printf("BLACKJACK! PUSH!\n");
    }
    else
    {
        char* buffer = malloc(BUFFSIZE);
        while(1)
        {
            printf("HIT (h) or STAND (s)\n");
            scanf("%s", buffer);

            if(strcmp (buffer, "h") == 0)
            {
                hit(&player, &d);
                show_hand (&player, "YOUR CARDS:");
                int value = hand_value (&player);
                if(value > 21)
                {
                    printf("BUST! YOU LOOSE! :(\n");
                    break;
                }
                else if(value == 21)
                    break;
            }
            else if(strcmp (buffer, "s") == 0)
                break;
        }
        free(buffer);

        int player_hand_value = hand_value (&player);
        int dealer_hand_value = hand_value (&dealer);

        if(player_hand_value <= 21)
        {
            printf("DEALERS TURN\n");

            dealer.size++;

            dealer_hand_value = hand_value (&dealer);
            show_hand (&dealer, "DEALERS CARDS:");
            int dealer_has_blackjack = hand_value (&dealer) == 21;

            if(!dealer_has_blackjack)
            {
                while(dealer_hand_value < 21 && dealer_hand_value <= player_hand_value)
                {
                    hit(&dealer, &d);
                    dealer_hand_value = hand_value (&dealer);
                    printf("DEALER GETS ANOTHER CARD...\n");
                    show_hand (&dealer, "DEALER'S CARDS:");
                }

                if(dealer_hand_value > 21)
                    printf("BUST! YOU WIN! :) \n");
                else if(dealer_hand_value == player_hand_value)
                    printf("PUSH!\n");
                else
                    printf("BUST! YOU LOOSE! :(\n");
            }
            else
            {
                printf("BLACKJACK! YOU LOOSE!\n");
            }
        }
    }


    free(cards);
    return 0;
}

