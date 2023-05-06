#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LIFEROCKS 0
#define LIFESUCKS 1
#define BYEBYELIFE 2
#define EXITGAME 3

#define STARVING 0
#define OVERFED 10

#define MIN_STOCK 0
#define MAX_STOCK 10

#define COWJOBFIRING 0
#define COWJOBPROMOTION 1

const int EVENT_PROBABILITIES[] = {25, 25}; // 25% chance of firing, 25% chance of promotion, arbitrary choice of values

const char* COW_FORMAT =
        "       ^__^\n"
        "      (%s)\\_______\n" // Eyes
        "     (__)\\        )\\/\\\n"
        "      %s ||----w |\n" // Tongue
        "         ||     ||\n"; 

int main() {
    // Initialize cow's starting state and attributes
    int cow_state = LIFEROCKS;
    int cow_health = 5;
    int stock = 5;
    int score = 0;
    int event = -1;

    // Seed the random number generator with current time
    srand(time(NULL));

    // Start the game loop
    while (cow_state != EXITGAME) {
        // Draw cow health automaton
        switch (cow_state) {
            case LIFEROCKS:
                printf("Liferocks (Healthy)\n");
                printf(COW_FORMAT, "uu", "U ");
                break;

            case LIFESUCKS:
                printf("Lifesucks (Unwell)\n");
                printf(COW_FORMAT, "VV", "j ");
                break;

            case BYEBYELIFE:
                // Exit the game loop if cow is dead
                cow_state = EXITGAME;
                break;
        }

        printf("Current stock level: %d\n", stock);

        // Declare a char array to store the user's input
        char input[10];

        printf("Enter amount of food to feed cow (0-%d): ", stock);
        fgets(input, sizeof(input), stdin);

        int lunchfood;
        
        if (sscanf(input, "%d", &lunchfood) != 1) {
            printf("Invalid input. Enter a valid integer between 0 and %d.\n", stock);
            continue;
        }

        if (lunchfood < 0 || lunchfood > stock) {
            printf("Invalid input. Enter a value between 0 and %d.\n", stock);
            continue;
        }

        // Generate random digestion value
        int digestion = rand() % 4 - 3;

        // Update cow's health and stock levels based on lunchfood and digestion
        cow_health += lunchfood + digestion;
        stock -= lunchfood;

        // Generate random crop value
        int crop = rand() % 7 - 3;

        // Update stock level based on crop
        stock += crop;

        // Reset event at the start of each iteration
        event = -1;
        if (rand() % 100 < EVENT_PROBABILITIES[COWJOBFIRING]) {
            event = COWJOBFIRING;
        } else if (rand() % 100 < EVENT_PROBABILITIES[COWJOBPROMOTION]) {
            event = COWJOBPROMOTION;
        }

        if (event == COWJOBFIRING) {
            printf("Oh no! You've been fired from your cow job at the cow factory, lose stock!\n");
            stock -= (rand() % 3 + 1);
        } else if (event == COWJOBPROMOTION) {
            printf("Woohoo! You've been promoted at your cow job, gain stock!\n");
            stock += (rand() % 3 + 1);
        }

        // Check if cow starved
        if (cow_health <= STARVING) {
            printf("Your cow starved! Game over!\n");
            cow_state = BYEBYELIFE;
            break;
        }
        // Check if cow is overfed
        if (cow_health >= OVERFED) {
            printf("You overfed your cow! Game over!\n");
            cow_state = BYEBYELIFE;
            break;
        }

        // Clamp cow's health level to STARVING and OVERFED
        if (cow_health < STARVING) {
            cow_health = STARVING;
        } else if (cow_health > OVERFED) {
            cow_health = OVERFED;
        }

        // Clamp stock level to MIN_STOCK and MAX_STOCK
        if (stock < MIN_STOCK) {
            stock = MIN_STOCK;
        } else if (stock > MAX_STOCK) {
            stock = MAX_STOCK;
        }
        
        //Useful for person correcting this to verify it works
        // printf("Crop: %d\n", crop);
        // printf("Digestion: %d\n", digestion);
        // printf("Cow's health level: %d\n", cow_health);

        // Check cow's health level and update state
        if (cow_health <= STARVING) {
            cow_state = BYEBYELIFE;
        } else if (cow_health >= 1 && cow_health <= 3 || cow_health >= 7 && cow_health <= 9) {
            cow_state = LIFESUCKS;
        } else {
            cow_state = LIFEROCKS;
        }
        score++;
    }
    //print score (+1 each turn) and dead cow
    printf("Score: %d\n", score);
    printf(COW_FORMAT, "xx", "  ");
    return 0;
}
