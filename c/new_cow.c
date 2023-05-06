#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define true 1

const char* COW_FORMAT[5] = {
        "       ^__^\n",
        "      (%s)\\_______\n", // Eyes
        "     (__)\\        )\\/\\\n",
        "      %s ||----w |\n", // Tongue
        "%s" // Variable Height
};

const char *COW_LEG_LINE[3] = {
    "       ||     ||\n",
    "        ||     ||\n",
    "         ||     ||\n"
};

const int MAX_LINE_LENGTH = 100;

char* repeat_string(const char* str, long N);
void affiche_vache(char* eyes, char* tongue, long height);
void update();
void gotoxy(int x, int y);

int main(int argc, char* argv[]) {
    char* file = argv[optind];

    if (file == NULL) {
        printf("Specify a file to open.\n");
        exit(1);
    }

    affiche_vache("fe", "fe", 1);
}

void affiche_vache(char* eyes, char* tongue, long height) {
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

char* read_first_line(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error: unable to open the file %s\n", file_path);
        return NULL;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, file);

    if (read == -1) {
        printf("Error: unable to read the first line of the file %s\n", file_path);
        free(line);
        fclose(file);
        return NULL;
    }

    // Remove newline character if present
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    fclose(file);
    return line;
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}
