#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

const char* COW_FORMAT = {
        "\\   ^__^\n"
        " \\  (%s)\\_______\n" // Eyes
        "    (__)\\        )\\/\\\n"
        "     %s ||----w |\n" // Tongue
        "%s" // Variable Height
};

const char* COW_LEG_LINE = "        ||     ||\n";

char* repeat_string(const char* str, long N);
void affiche_vache(char* eyes, char* tongue, long height, int frame);
void update();
void gotoxy(int x, int y);

int main(int argc, char* argv[]) {
    int option;
    char* valeurE = "oo";
    char* valeurT = "  ";
    long valeurHeight = 1;
    char* endptr; // used in str to long conversion
    while ((option = getopt(argc, argv, "e:T:H:h")) != -1) {
        switch (option) {
            // Eye String
            case 'e':
                valeurE = optarg;
                break;

                // Tongue String
            case 'T':
                valeurT = optarg;
                break;

            case 'H':
                valeurHeight = strtol(optarg, &endptr, 10);

                // If there was an error converting the string
                if (*endptr != '\0') {
                    fprintf(stderr, "Error converting %s to a long.\n", optarg);
                    exit(1);
                }
                break;

                // Help / Usage Instructions.
            case 'h':
                printf("Usage: %s -e [v] -T [v] -h\n", argv[0]);
                exit(0);
                break;

            default:
                fprintf(stderr, "Usage: %s -e [v] -T [v] -h\n", argv[0]);
                return 1;
        }
    }

    int frame = 0;
    while (1) {
        affiche_vache(valeurE, valeurT, valeurHeight, frame);
        usleep(500000); // Pause for 500 ms
        update();
        frame = (frame + 1) % 2;
    }

    return 0;
}

void affiche_vache(char* eyes, char* tongue, long height, int frame) {
    if (strlen(eyes) != 2) {
        fprintf(stderr, "Invalid eyes: %s. Must be exactly 2 characters.\n", eyes);
        exit(1);
    }

    if (strlen(tongue) != 2) {
        fprintf(stderr, "Invalid Tongue: %s. Must be exactly 2 characters.\n", tongue);
        exit(1);
    }

    if (height < 1 || height > 10) {
        fprintf(stderr, "Invalid Height, must be between 1 and 10\n");
        exit(1);
    }

    char* legs = repeat_string(COW_LEG_LINE, height);
    printf(COW_FORMAT[frame], eyes, tongue, legs);
    free(legs);
}

char* repeat_string(const char* str, long N) {
// Allocate memory for the new string
    int len = (int) strlen(str);
    char *new_str = (char *) malloc((N * len + 1) * sizeof(char));
    if (new_str == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new string.\n");
        exit(1);
    }

    // Copy N copies of the original string into the new string
    for (int i = 0; i < N; i++) {
        strcat(new_str, str);
    }

    return new_str;
}

// \33[H is the cursor home sequence
// \033[J is the clear screen sequence
void update() {
    printf("\33[H\033[J");
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}