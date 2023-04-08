#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Header
char* read_input_from_stdin();
char* read_input_from_command_line(int argc, char* argv[]);
char** split_string(char* str);
char* get_chars(char c, int n);
void drawThoughtBox(char* input, char** substrings);
void print_file(const char *filename);

//Constants
#define MAX_LINE_LENGTH 39 // When to break sentences to the next line

int main(int argc, char* argv[]) {
    char *cowFile = "cows/default.cow";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-file") == 0 && i + 1 < argc) {
            cowFile = argv[i+1];
        }
    }

    char* input;

    // Determine whether or not to read from stdin or the commandline
    if (argc > 1) {
        input = read_input_from_command_line(argc, argv);
    } else {
        input = read_input_from_stdin();
    }

    // Turn the input into a list of strings
    char** substrings = split_string(input);

    // Draw the textbox
    drawThoughtBox(input, substrings);

    // Draw the rest of the cow
    print_file(cowFile);

    free(input);
    return 0;
}

void drawThoughtBox(char*input, char** substrings) {
    unsigned long inputLength = strlen(input);
    unsigned long lineCount = (inputLength + MAX_LINE_LENGTH - 1) / MAX_LINE_LENGTH;

    unsigned long cowLineLength = (inputLength <= MAX_LINE_LENGTH ? inputLength : MAX_LINE_LENGTH) + 2;

    // TODO free memory from get_chars
    printf(" %s\n", get_chars('_', (int) cowLineLength));
    for (int i = 0; i < lineCount; i++) {
        if (i == 0) {
            printf("/ %s \\\n", substrings[i]);
        } else if (i == lineCount-1) {
            char* extraSpaces = "";
            unsigned long lastLineLength = strlen(substrings[i]);
            if (lastLineLength < MAX_LINE_LENGTH) {
                extraSpaces = get_chars(' ', (int) (MAX_LINE_LENGTH-lastLineLength));
            }
            printf("\\ %s%s /\n", substrings[i], extraSpaces);
        } else {
            printf("| %s |\n", substrings[i]);
        }

        free(substrings[i]);
    }

    printf(" %s\n", get_chars('-', (int) cowLineLength));
}

// Take a string from stdin and return it
char* read_input_from_stdin() {
    char* input = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&input, &len, stdin);

    if (read == -1) {
        printf("Erreur: Pas de contenu dans STDIN.\n");
        exit(EXIT_FAILURE);
    }

    // Remove the newline character at the end of the input
    input[strcspn(input, "\n")] = '\0';

    return input;
}

char* read_input_from_command_line(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Erreur: Aucun contenu fourni en argument.\n");
        exit(EXIT_FAILURE);
    }

    char* input = strdup(argv[1]);

    return input;
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

// Prenez le contenu du fichier au chemin fourni et imprimez son contenu
void print_file(const char *filename) {
    FILE *file;
    char ch;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier: %s\n", filename);
        return;
    }

    while ((ch = (char) fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
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