#include "blackjack.h"

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
