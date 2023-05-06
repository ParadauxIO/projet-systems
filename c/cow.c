#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LIFEROCKS 0
#define LIFESUCKS 1
#define BYEBYELIFE 2

#define STARVING 0
#define OVERFED 10

#define MIN_STOCK 0
#define MAX_STOCK 10

const char* COW_FORMAT =
        "       ^__^\n"
        "      (%s)\\_______\n" // Eyes
        "     (__)\\        )\\/\\\n"
        "      %s ||----w |\n" // Tongue
        "         ||     ||\n"; // Variable Height

int main() {
    int cow_state = LIFEROCKS;
    int cow_health = 5;
    int stock = 5;

    srand(time(NULL));

    while (cow_state != BYEBYELIFE) {
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
                printf("Byebyelife (Dead)\n");
                printf(COW_FORMAT, "xx", "  ");
                break;
        }

        printf("Cow's health level: %d\n", cow_health);
        printf("Current stock level: %d\n", stock);

        int lunchfood;
        printf("Enter amount of food to feed cow (0-%d): ", stock);
        scanf("%d", &lunchfood);

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

        // Check if cow is overfed
        if (cow_health >= OVERFED) {
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
        printf("crop: %d\n", crop);
        printf("digestion: %d\n", digestion);
        // Check cow's health level and update state
        if (cow_health <= STARVING) {
            cow_state = BYEBYELIFE;
        } else if (cow_health >= 1 && cow_health <= 3 || cow_health >= 7 && cow_health <= 9) {
            cow_state = LIFESUCKS;
        } else {
            cow_state = LIFEROCKS;
        }
    }

    printf("Your cow is dead. Game over!\n");

    return 0;
}
