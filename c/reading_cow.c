#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define true 1

const char* COW_FORMAT[5] = {
        "       ^__^\n",
        "      (%s)\\_______\n", // Eyes
        "     (__)\\        )\\/\\\n",
        "      %c  ||----w |\n", // Tongue
        "%s" // Variable Height
};

const char *COW_LEG_LINE[3] = {
        "       ||     ||\n",
        "        ||     ||\n",
        "         ||     ||\n"
};

const int MAX_LINE_LENGTH = 100;

char* repeat_string(const char* str, long N);
void affiche_vache(char* eyes, char tongue, long height);
void update();
char** split_string(char* str);
char* get_chars(char c, int n);
void drawThoughtBox(size_t inputLength, char** substrings);

int main(int argc, char* argv[]) {
    char* filePath = argv[1];
    char* message = (char*) malloc(100 * sizeof(char));
    FILE *file;
    char ch;
    char lastArrIndex = 0;

    if (filePath == NULL) {
        printf("Specify a file to open lol.\n");
        exit(1);
    }

    // Open the file for reading
    file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    strcpy(message, "");
    // Loop through every character in the file
    while ((ch = (char) fgetc(file)) != EOF) {
        // Do something with the character
        update();

        message[lastArrIndex] = ch;
        lastArrIndex++;
        char** substrings = split_string(message);
        drawThoughtBox(strlen(message), substrings);
        affiche_vache("oo", ch, 1);
        sleep(1);
    }

    // Close the file
    fclose(file);

    // Free the message
    free(message);
}

void affiche_vache(char* eyes, char tongue, long height) {
    if (strlen(eyes) != 2) {
        fprintf(stderr, "Invalid eyes: %s. Must be exactly 2 characters.\n", eyes);
        exit(1);
    }

    if (height < 1 || height > 10) {
        fprintf(stderr, "Invalid Height, must be between 1 and 10\n");
        exit(1);
    }

    char* legs = repeat_string(COW_LEG_LINE[2], height);
    printf("%s", COW_FORMAT[0]);
    printf(COW_FORMAT[1], eyes);
    printf("%s", COW_FORMAT[2]);
    printf(COW_FORMAT[3], tongue);
    printf(COW_FORMAT[4], legs);
    free(legs);
}

char* repeat_string(const char* str, long N) {
    // Allocate memory for the new string
    int len = (int) strlen(str);
    char* new_str = (char*) malloc((N*len + 1) * sizeof(char));
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
    printf("\033[2J"); // clear the screen
}

void drawThoughtBox(size_t inputLength, char** substrings) {
    // The length of the substrings array
    unsigned long lineCount = (inputLength + MAX_LINE_LENGTH - 1) / MAX_LINE_LENGTH;

    // The length of each line
    unsigned long cowLineLength = (inputLength <= MAX_LINE_LENGTH ? inputLength : MAX_LINE_LENGTH) + 2;

    // Print the header
    char* header = get_chars('_', (int) cowLineLength);
    printf(" %s\n", header);

    // For every line in substrings
    for (int i = 0; i < lineCount; i++) {
        if (i == 0) {
            // / Text \
            printf("/ %s \\\n", substrings[i]);
        } else if (i == lineCount-1) {
            // It's possible we won't need extraSpaces
            char* extraSpaces = "";
            unsigned long lastLineLength = strlen(substrings[i]);
            // Generate extra spaces for padding if necessary
            if (lastLineLength < MAX_LINE_LENGTH) {
                extraSpaces = get_chars(' ', (int) (MAX_LINE_LENGTH-lastLineLength));
            }
            // \ Text /
            printf("\\ %s%s /\n", substrings[i], extraSpaces);

            // Free dynamically allocated extra spaces
            free(extraSpaces);
        } else {
            printf("| %s |\n", substrings[i]);
        }

        // Free the line
        free(substrings[i]);
    }

    char* footer = get_chars('-', (int) cowLineLength);
    printf(" %s\n", footer);

    free(header);
    free(footer);
}

char** split_string(char* str) {
    const int MAX_LEN = 39;
    unsigned long len = strlen(str);
    int start = 0;
    unsigned long substr_count = (len + MAX_LEN - 1) / MAX_LEN; // calculer le nombre de sous-chaînes nécessaires
    char** substrs = (char**) malloc(substr_count * sizeof(char*)); // allouer de la mémoire pour le tableau de sous-chaînes

    if (!substrs) {
        printf("Erreur: Impossible d'allouer de la mémoire.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < substr_count; i++) {
        unsigned long copy_len = len - start > MAX_LEN ? MAX_LEN : len - start;
        substrs[i] = (char*) malloc((copy_len + 1) * sizeof(char)); // Pour la sous-chaîne
        if (!substrs[i]) {
            printf("Erreur: Impossible d'allouer de la mémoire. (II)\n");
            exit(EXIT_FAILURE);
        }

        strncpy(substrs[i], str + start, copy_len);
        substrs[i][copy_len] = '\0';
        start += MAX_LEN;
    }

    return substrs;
}

// Prenez un caractère et un nombre et renvoyez une chaîne contenant autant de copies du caractère
char* get_chars(char c, int n) {
    char* str = (char*) malloc(sizeof(char) * (n + 1));

    // Remplir la chaîne
    for (int i = 0; i < n; i++) {
        str[i] = c;
    }

    // "Null Terminate" la chaîne
    str[n] = '\0';
    return str;
}