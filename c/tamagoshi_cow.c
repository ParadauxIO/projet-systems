#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LIFEROCKS 0
#define LIFESUCKS 1
#define BYEBYELIFE 2

// Cow health levels
#define STARVING 0
#define OVERFED 10

// Min - Max food stock levels
#define MIN_STOCK 0
#define MAX_STOCK 10

// Random events
#define COW_JOB_FIRING 0
#define COW_JOB_PROMOTION 1

#define MAX_SCORES 5

// Cow ASCII art
const char* COW_FORMAT =
        "       ^__^\n"
        "      (%s)\\_______\n" // Eyes
        "     (__)\\        )\\/\\\n"
        "      %s ||----w |\n" // Tongue
        "         ||     ||\n";

// 25% chance of firing, 25% chance of promotion, arbitrary choice of values
const int EVENT_PROBABILITIES[] = {25, 25};

void show_scores();
void save_score(int score);
void affiche_vache(char* title, char* eyes, char* tongue);
int enforce_int_constraints(int val, int min, int max);
int rand_range(int lower, int upper);
void update();

struct score {
    int value;
    char name[10];
    char date[20];
};

int main() {
    // Stores current state of the cow
    int cow_state = LIFEROCKS;

    // Represents its overall health, not to be disclosed to the user
    int cow_health = 5;

    int stock = 5;
    int score = 0;

    // Strings of fixed length to store various event messages / errors
    char invalid_input_message[100] = "";
    char event_message[100] = "";

    // Seed the random number generator with current time
    srand(time(NULL));

    while (cow_state != BYEBYELIFE) {
        // Clear the screen
        update();

        // Print the messages from the previous iteration
        printf("\n%s%s\n", invalid_input_message, event_message);

        // Reset the messages
        strcpy(invalid_input_message, "");
        strcpy(event_message, "");

        // Draw the cow based on its current state
        switch (cow_state) {
            case LIFEROCKS:
                affiche_vache("LIFEROCKS! (Healthy)","uu", "U ");
                break;
            case LIFESUCKS:
                affiche_vache("LIFESUCKS! (Unwell)","VV", "j ");
                break;
            default:
                fprintf(stderr, "The game reached an invalid state: %d.", cow_state);
                exit(1);
        }

        printf("Current stock level: %d\n", stock);

        int food_given;
        printf("Enter amount of food to feed the cow (0-%d): ", stock);

        // Check for non-numeric input
        if (scanf("%d", &food_given) != 1) {
            sprintf(invalid_input_message, "Invalid input. Enter a valid integer between 0 and %d.\n", stock);

            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            // Go back to the prompt loop
            continue;
        }

        // Check for too small or too large of an input
        if (food_given < 0 || food_given > stock) {
            sprintf(invalid_input_message, "Invalid input. Enter a value between 0 and %d.\n", stock);

            // Go back to the prompt loop
            continue;
        }

        // Generate random digestion value
        int digestion = rand_range(-3, 0);

        // Update cow's health and stock levels based on food_given and digestion
        cow_health += food_given + digestion;
        stock -= food_given;

        // Generate random crop value
        int crop = rand_range(-3, 3);

        // Update stock level based on crop
        stock += crop;

        // Your cow got fired from their job
        if (rand_range(0, 100) < EVENT_PROBABILITIES[COW_JOB_FIRING]) {
            sprintf(event_message, "Oh no! You've been fired from your cow job at the cow factory, lose stock!\n");
            stock -= (rand_range(1, 3));

        // Your cow got a promotion at their job
        } else if (rand_range(0, 100) < EVENT_PROBABILITIES[COW_JOB_PROMOTION]) {
            sprintf(event_message, "Woohoo! You've been promoted at your cow job, gain stock!\n");
            stock += (rand_range(1, 3));
        }
        
        // Useful for person correcting this
        // printf("Crop: %d\n", crop);
        // printf("Digestion: %d\n", digestion);
        // printf("Cow's health level: %d\n", cow_health);

        // Check if cow starved
        if (cow_health <= STARVING) {
            cow_state = BYEBYELIFE;

            // Check if cow was overfed
        } else if (cow_health <= 3 || cow_health >= 7 && cow_health <= 9) {
            cow_state = LIFESUCKS;

            // The player successfully lasted another turn.
            score++;
        } else {
            cow_state = LIFEROCKS;

            // The player successfully lasted another turn.
            score++;
        }

        // Ensure stock/health does not exceed or goes below the max/min respectively
        cow_health = enforce_int_constraints(cow_health, STARVING, OVERFED);
        stock = enforce_int_constraints(stock, MIN_STOCK, MAX_STOCK);
    }

    // Clears the screen at the end of the game
    update();

    // Prints the lose condition
    if (cow_health <= STARVING) {
        printf("Your cow starved! Game over!\n");;
    } else if (cow_health >= OVERFED) {
        printf("You overfed your cow! Game over!\n");
    }

    // Cow is dead if it has exited the loop
    affiche_vache("BYEBYELIFE! (Dead)", "xx", "  ");

    printf("Score: %d\n", score);
    save_score(score);
    show_scores();
}

int enforce_int_constraints(int val, int min, int max) {
    if (val > max) {
        val = max;
    } else if (val < min) {
        val = min;
    }

    return val;
}


void affiche_vache(char* title, char* eyes, char* tongue) {
    if (title == NULL || strlen(title) == 0) {
        fprintf(stderr, "Invalid title.");
    }

    if (strlen(eyes) != 2) {
        fprintf(stderr, "Invalid eyes: %s. Must be exactly 2 characters.\n", eyes);
        exit(1);
    }

    if (strlen(tongue) != 2) {
        fprintf(stderr, "Invalid Tongue: %s. Must be exactly 2 characters.\n", tongue);
        exit(1);
    }

    printf("%s\n\n", title);
    printf(COW_FORMAT, eyes, tongue);
}

void save_score(int score) {
    struct score scores[MAX_SCORES];
    int i, j, inserted = 0;
    time_t t;
    struct tm* tm_info;
    char date_string[20];

    // Get the current date as a string
    time(&t);
    tm_info = localtime(&t);
    strftime(date_string, sizeof(date_string), "%Y-%m-%d", tm_info);

    // Open the scores file for reading and writing
    FILE* file = fopen("scores.txt", "r+");
    if (file == NULL) {
        printf("Error: Could not open scores file\n");
        return;
    }

    // Read the scores from the file into the scores array
    for (i = 0; i < MAX_SCORES; i++) {
        if (fscanf(file, "%d %s %s\n", &scores[i].value, scores[i].name, scores[i].date) != 3) {
            scores[i].value = 0;
            strcpy(scores[i].name, "");
            strcpy(scores[i].date, "");
        }
    }

    // Try to insert the new score into the sorted scores array
    for (i = 0; i < MAX_SCORES; i++) {
        if (score > scores[i].value) {
            // Shift the lower scores down to make room for the new score
            for (j = MAX_SCORES - 1; j > i; j--) {
                scores[j] = scores[j-1];
            }

            // Insert the new score and get the player's name
            scores[i].value = score;
            printf("Congratulations! You got a new high score of %d.\n", score);
            printf("Enter your name: ");
            scanf("%s", scores[i].name);
            strcpy(scores[i].date, date_string);
            inserted = 1;
            break;
        }
    }

    // If the new score was not inserted, inform the player and close the file
    if (!inserted) {
        printf("Sorry, your score of %d did not make it to the top %d.\n", score, MAX_SCORES);
        fclose(file);
        return;
    }

    // Update the scores file with the new scores
    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), 0);
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

int rand_range(int lower, int upper) {
    // scale and shift the value to the desired range
    return lower + rand() % (upper - lower + 1);
}

void update() {
    printf("\033[H\033[J");
}