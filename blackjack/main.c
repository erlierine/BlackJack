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

int main(int argc, char** argv)
{
    if(argc <2)
    {
        // First way of processing command line args
        // printf("usage: %s <input_folder>\n", argv[0]);
        // error(EXIT_FAILURE);

        // Second way is by calling our error func
        // char error_msg[MSG_LENGTH];
        // strcpy(error_msg, "usage: ");
        // strcat(strcat(error_msg , argv[0]),  "<input_folder>\n");
        // error(error_msg, EXIT_FAILURE);

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

