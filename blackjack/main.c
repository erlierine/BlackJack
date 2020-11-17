#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_LENGTH 200

void error(char* msg, int exit_code)
{
    printf ("%s\n", msg);
    exit(exit_code);
}

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

