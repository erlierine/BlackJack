#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_LENGTH 200
#define MAX_PATH_LEN 100

enum card_type{
    C_ACE = 1,
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

void make_cards() {
    int i;
    FILE *f;
    for(i=2;i<10;i++) {
        char file_path[MAX_PATH_LEN];
        sprintf (file_path, "cards/%d.txt", i);
        file_path[strlen (file_path) - 1] = '\0';
        printf("%s", file_path);
        f = fopen(file_path, "w");
        fprintf(f, "*********\n");
        fprintf(f, "*       *\n");
        fprintf(f, "*       *\n");
        fprintf(f, "*   %d   *\n", i);
        fprintf(f, "*       *\n");
        fprintf(f, "*       *\n");
        fprintf(f, "*********\n");
//        fclose (f);
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

int main(int argc, char** argv)
{
    make_cards ();
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

    return 0;
}

