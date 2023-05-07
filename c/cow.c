#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Cow states
#define LIFEROCKS 0
#define LIFESUCKS 1
#define BYEBYELIFE 2
#define EXITGAME 3

// Cow health levels
#define STARVING 0
#define OVERFED 10

// Min - Max food stock levels
#define MIN_STOCK 0
#define MAX_STOCK 10

// Random events
#define COW_JOB_FIRING 0
#define COW_JOB_PROMOTION 1

// 25% chance of firing, 25% chance of promotion, arbitrary choice of values
const int EVENT_PROBABILITIES[] = {25, 25};

// Maximum number of scores saved on the leaderboard
#define MAX_SCORES 5

// Cow ASCII art
const char* COW_FORMAT =
        "       ^__^\n"
        "      (%s)\\_______\n" // Eyes
        "     (__)\\        )\\/\\\n"
        "      %s ||----w |\n" // Tongue
        "         ||     ||\n"; 

void show_scores();
void save_score(int score);
void update();

int main() {
    // Initialize cow's starting state and attributes
    int cow_state = LIFEROCKS;
    int cow_health = 5;
    int stock = 5;
    int score = 0;
    int event = -1;

    char invalid_input_message[100] = "";
    char event_message[100] = "";

    // Seed the random number generator with current time
    srand(time(NULL));

    // Start the game loop
    while (cow_state != EXITGAME) {
        
        // Clear the console screen
        update();

        // Print the messages from the previous iteration
        printf("%s%s", invalid_input_message, event_message);

        // Reset the messages
        strcpy(invalid_input_message, "");
        strcpy(event_message, "");

        // Draw the cow to represent its respective state
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

        // Get user input
        char input[10];

        printf("Enter amount of food to feed the cow (0-%d): ", stock);
        fgets(input, sizeof(input), stdin);

        int lunchfood;
        
        if (sscanf(input, "%d", &lunchfood) != 1) {
            sprintf(invalid_input_message, "Invalid input. Enter a valid integer between 0 and %d.\n", stock);
            continue;
        }

        if (lunchfood < 0 || lunchfood > stock) {
            sprintf(invalid_input_message, "Invalid input. Enter a value between 0 and %d.\n", stock);
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
        if (rand() % 100 < EVENT_PROBABILITIES[COW_JOB_FIRING]) {
            event = COW_JOB_FIRING;
        } else if (rand() % 100 < EVENT_PROBABILITIES[COW_JOB_PROMOTION]) {
            event = COW_JOB_PROMOTION;
        }

        if (event == COW_JOB_FIRING) {
            sprintf(event_message, "Oh no! You've been fired from your cow job at the cow factory, lose stock!\n");
            stock -= (rand() % 3 + 1);
        } else if (event == COW_JOB_PROMOTION) {
            sprintf(event_message, "Woohoo! You've been promoted at your cow job, gain stock!\n");
            stock += (rand() % 3 + 1);
        }

        // Check if cow starved
        if (cow_health <= STARVING) {
            update();
            printf("Your cow starved! Game over!\n");
            cow_state = BYEBYELIFE;
            break;
        }

        // Check if cow is overfed
        if (cow_health >= OVERFED) {
            update();
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
        
        // Useful for person correcting this to verify it works
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
    printf(COW_FORMAT, "xx", "  ");
    // print score (+1 each turn)
    printf("Score: %d\n", score);
    save_score(score);
    show_scores();
    return 0;
}

struct score {
    int value;
    char name[50];
    char date[11];
};

void save_score(int score) {
    struct score scores[MAX_SCORES];
    // inserted tracks if the score was added to the high scores
    int i, j, inserted = 0;
    time_t t;
    struct tm* tm_info;
    char date_string[20];

    // Get the current date
    time(&t);
    tm_info = localtime(&t);
    strftime(date_string, sizeof(date_string), "%Y-%m-%d", tm_info);

    // Open the scores file for reading and writing
    FILE* file = fopen("scores.txt", "r+");
    if (file == NULL) {
        printf("Error: Could not open scores file\n");
        return;
    }

    // Read the scores from the file
    for (i = 0; i < MAX_SCORES; i++) {
        if (fscanf(file, "%d %s %s\n", &scores[i].value, scores[i].name, scores[i].date) != 3) {
            scores[i].value = 0;
            strcpy(scores[i].name, "");
            strcpy(scores[i].date, "");
        }
    }

    // Insert the new score into the list
    for (i = 0; i < MAX_SCORES; i++) {
        if (score > scores[i].value) {
            // Shift the other scores down
            for (j = MAX_SCORES - 1; j > i; j--) {
                scores[j] = scores[j-1];
            }

            // Insert the new score
            scores[i].value = score;
            printf("Congratulations! You got a new high score of %d.\n", score);
            printf("Enter your name: ");
            scanf("%s", scores[i].name);
            strcpy(scores[i].date, date_string);
            inserted = 1;
            break;
        }
    }

    // If the new score was not inserted, do not update the file
    if (!inserted) {
        printf("Sorry, your score of %d did not make it to the top %d.\n", score, MAX_SCORES);
        fclose(file);
        return;
    }

    // Truncate the file and write the new scores to it
    fseek(file, 0, SEEK_SET);
    ftruncate(filen  o(file), 0);
    for (i = 0; i < MAX_SCORES; i++) {
        fprintf(file, "%d %s %s\n", scores[i].value, scores[i].name, scores[i].date);
    }

    fclose(file);
}

void show_scores() {
    struct score scores[MAX_SCORES];
    int i;

    // Open the scores file for reading
    FILE* file = fopen("scores.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open scores file\n");
        return;
    }

    // Read the scores from the file
    for (i = 0; i < MAX_SCORES; i++) {
        if (fscanf(file, "%d %49s %49s\n", &scores[i].value, scores[i].name, scores[i].date) != 3) {
            scores[i].value = 0;
            strcpy(scores[i].name, "");
            strcpy(scores[i].date, "");
        }
    }

    // Display the scores
    printf("High Scores:\n");
    printf("%-4s %-15s %-10s %s\n", "Rank", "Name", "Score", "Date");
    printf("----------------------------------------\n");
    for (i = 0; i < MAX_SCORES; i++) {
        if (strlen(scores[i].name) > 0) {
            printf("%-4d %-15s %-10d %s\n", i+1, scores[i].name, scores[i].value, scores[i].date);
        }
    }

    fclose(file);
}

void update() {
    printf("\033[H\033[J");
}