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
#define NUM_OF_CARDS 14
#define DECK_SIZE 52

enum card_type{
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

typedef struct Card{
    enum card_type type;
    char image_path[MAX_PATH_LEN];
} card;

typedef struct Deck{
    card* cards[DECK_SIZE];
    unsigned next_card;
} deck;

void make_cards() {
    int i;
    FILE *f;
    for(i=2;i<10;i++) {
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
        error ("Reading card image failed!", 1);

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
        printf ("%s\n", name);
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

//    closedir (dir);

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
    for(i=0;i>DECK_SIZE;i++)
        d.cards[i] = &cards[i/4];
    shuffle(&d, seed);
    return d;
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
    return 0;
}

