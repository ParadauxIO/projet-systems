# Cowsay Project

In this project we learn about Cowsay, a perl project orginonally started for the author
to learn the Perl Programming language. The project is now completely unmaintained but 
the source code is readily available online in its original Perl. We also consulted the 
detailed manpage for the project.

**N.B**: Complete solutions for each file can be found in the Appendix. 

## Sections

- Bash
  - cow_kindergarten.sh
  - cow_primaryschool.sh
  - cow_highschool.sh
  - cow_college.sh
  - cow_university.sh
  - smart_cow.sh
  - crazy_cow.sh
- C
  - cowsay.c
  - cowsay_tamagotchi.c
- Appendix

## Bash

### cow_kindergarten

## C
### newcow.c

1. Créer une fonction affiche vache qui affiche simplement une vache sans la bulle de text

```c
#include <stdio.h>

# Displays a fixed-string representation of a cow missing a speech bubble
void affiche_vache() {
    # Creates a string which contains the ascii art representation of a cow
    # Makes use of string literal concatenation.
    char* my_cow =
                "\\   ^__^\n"
                " \\  (oo)\\_______\n"
                "    (__)\\        )\\/\\\n"
                "        ||----w |\n"
                "        ||     ||\n";
    
    # Prints the string literal as an argument.
    printf("%s", my_cow);
}

int main() {
    # Prints the cow to STDOUT
    affiche_vache();
    return 0; # Report back that everything went well
}
```

While implementing this we only ran into one major issue, taking the cow example from the project 
presentation and placing it as a literal in our code. We ended up having to retype it and add in 
the proper escape sequences (for the \ character as well as for newlines.)

We laid out the string literal using string literal concatenation for readability’s sake, although
you could just as easily use a single line and rely on your text editor's text wrapping function.
At runtime, there is no difference from what we could tell.

2. TODO

We can implement command-line arguments using C's `getopt()` function within `unistd.h`. We did
this by using a while loop to get the values of all possible options (h,T,e)

```c
int option;
while ((option = getopt(argc, argv, "e:T:h")) != -1) {}
```

The option variable is only to be used in the loop as an iterator of sorts, each flag will have 
its own variable to store its respective state. The important thing to note here is the string
`"e:T:h"` which tells getopt what options to expect, specifically 'e' and 'T' which take a value
and h which does not (denoted by the presence of a colon.)

This can be expanded then to save the values:
```c
int main(int argc, char* argv[]) {
    int option;
    char* valeurE = NULL;
    char* valeurT = NULL;

    while ((option = getopt(argc, argv, "e:T:h")) != -1) {
        switch (option) {
            // Eye String
            case 'e':
                valeurE = optarg;
                break;

            // Tongue String
            case 'T':
                valeurT = optarg;
                break;

            // Help / Usage Instructions.
            case 'h':
                printf("Here's some help!");
                exit(0);

            default:
                fprintf(stderr, "Usage: %s -e [v] -T [v] -h\n", argv[0]);
                return 1;
        }
    }

    if (valeurE != NULL) {
        printf("The value of eyes: %s\n", valeurE);
    }

    if (valeurT != NULL) {
        printf("The value of tongue: %s\n", valeurT);
    }

    return 0;
}
```

-T for the tongue string, and a generic -h flag are what we chose to take from cowsay 
to reimplement.

The main implementaiton changes were in affiche_vache which now looks like follows:
```c
const char* COW_FORMAT =
        "\\   ^__^\n"
        " \\  (%s)\\_______\n"
        "    (__)\\        )\\/\\\n"
        "     %s ||----w |\n"
        "        ||     ||\n";

void affiche_vache(char* eyes, char* tongue) {
    char cow[85];

    if (eyes == NULL) {
        eyes = "oo";
    } else if (strlen(eyes) != 2) {
        fprintf(stderr, "Invalid eyes: %s. Must be exactly 2 characters.", eyes);
        exit(1);
    }

    if (tongue == NULL) {
        tongue = "  "; // Two space characters
    } else if (strlen(tongue) != 2) {
        fprintf(stderr, "Invalid Tongue: %s. Must be exactly 2 characters.", tongue);
        exit(1);
    }

    printf(COW_FORMAT, eyes, tongue);
}
```

It was also at this point we realised the static cow literal could be a constant aptly named "COW_FORMAT"
The implementation of the tongue and eyes were rather trivial.

We enforced the fact that the eyes and tongue have to be 2 characters to avoid having to 
implement text wrapping. If either eyes or tongue are missing then defaults are provided:
"oo" for the eyes or two space characters for tongue (i.e., no tongue)

If they are not `NULL` but not exactly two characters than an error is put to STDERR explaining this and
exits with a non-zero status code to indicate an error.

We modified the cow format string to have two "%s" format specifiers for each the eyes and tongue. 
We use printf to fill in the values for this.

In order to implement the menu we added a case in our switch/case for 'h' which prints the help
information then exits with a 0 status code:
```c
case 'h':
    printf("Usage: %s -e [v] -T [v] -h\n", argv[0]);
    exit(0);
```

No need for a `break` considering it would be unreachable. 

3. Creative technical step

We decided to make the cow have a variable height by extending the amount of leg lines the cow has
based on the value of the parameter `-H` not to be confused by `-h` for help.

```bash
$ newcow -e hi -H 5
```

```text
\   ^__^
 \  (hi)\_______
    (__)\        )\/\
        ||----w |
        ||     ||
        ||     ||
        ||     ||
        ||     ||
        ||     ||
```

We did this by implementing a function `repeat_string` which takes a constant string `str` and the 
number of types you'd like it to be repeated `N` and concatenates N copies of that string together
as a new string using dynamic memory allocation which is later freed to avoid leaks. 

```c
char* repeat_string(const char* str, long N) {
    // Allocate memory for the new string
    int len = (int) strlen(str);
    char* new_str = (char*) malloc((N*len + 1) * sizeof(char));
    if (new_str == NULL) {
        // If for some reason we can't allocate the memory, exit
        fprintf(stderr, "Error: Failed to allocate memory for new string.\n");
        exit(1);
    }

    // Copy N copies of the original string into the new string
    for (int i = 0; i < N; i++) {
        strcat(new_str, str);
    }

    return new_str;
}
```

We then used this alongside a new constant to refer to the leg line to implement
the variable legs:
```c
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

    char* legs = repeat_string(COW_LEG_LINE, height);
    printf(COW_FORMAT, eyes, tongue, legs);
    free(legs);
}
```

It was at this point we noticed another improvement we could make.
Rather than defaulting valeurH and valeurE to NULL we could just make
them the default values of "oo" and "  " and skip the NULL check.

The changes to the main function are as follows:
```c 
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

    affiche_vache(valeurE, valeurT, valeurHeight);
    return 0;
}
```

4. gotoxy / update

In terms of what the two functions presented do, it is pretty straight forward.
They make use of ANSI escape codes to perform meta tasks to the terminal emulator.

- `gotoxy(int x, int y)` takes an x and a y coordinate and moves it to the specified coordinates. 
- `update()` performs two escape code sequences. `\33[H` is to bring the cursor back to the top left (`H` for home)
`\033[J` clears the screen

For this part of the project we chose to implement a "moonwaling cow", a cow that walks 
backwards like Michael Jackson's Signature move. 

For this we used update() to clear the screen, and gotoxy() to change the position of the 
cow on the screen towards the right. 

We had to make a few changes to our code for this to work. 

Firstly, we modified the COW_FORMAT to be an array so we could
manipulate each line of the cow (For moving it across the screen)

```c
const char* COW_FORMAT[5] = {
        "       ^__^\n",
        "      (%s)\\_______\n", // Eyes
        "     (__)\\        )\\/\\\n",
        "      %s ||----w |\n", // Tongue
        "%s" // Variable Height
};
```

And for the COW_LEG_LINE string we also made it an array, where each
element is a different frame in the animation (forward, neutral, backwards)

```c
const char *COW_LEG_LINE[3] = {
    "       ||     ||\n",
    "        ||     ||\n",
    "         ||     ||\n"
};
```

We then updated `affiche_vache` to take an x and y position as well
as a frame variable which will control which leg it displays. 

We also changed the way the cow is drawn to work with the new array type
we've made:
```c
void affiche_vache(char* eyes, char* tongue, long height, int frame, int x, int y) {
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

    if (frame > 2) {
        fprintf(stderr, "Invalid Frame, must be between 0 and 2\n");
        exit(1);
    }

    char* legs = repeat_string(COW_LEG_LINE[frame], height);
    gotoxy(x, y);
    printf("%s", COW_FORMAT[0]);
    gotoxy(x, y+1);
    printf(COW_FORMAT[1], eyes);
    gotoxy(x, y+2);
    printf("%s", COW_FORMAT[2]);
    gotoxy(x, y+3);
    printf(COW_FORMAT[3], tongue);
    gotoxy(x, y+4);
    printf(COW_FORMAT[4], legs);
    free(legs);
}
```

While it's possible to use a loop to print the cow, We found it was
needlessly complicated due to the use of format specifiers in the strings
It's much cleaner to just print them out by index and pass in the relevant
data (eyes, tongue or legs)

We then added an endless loop at the end of our  `main()`

```c
  int frame = 0;
  int x = 50, y = 0;
  while (true) {
      affiche_vache(valeurE, valeurT, valeurHeight, frame, x, y);
      usleep(200000); // Pause for 200 ms
      update(x, y);
      frame++;
      if (frame > 2) {
          frame = 0;
      }
      x += 1;
      y += 1;
  }
```

This loops through the values for x and y and has the cow move to the right
and pauses for 200 ms before moving on.

5. Reading cow

The first step to implementing the reading cow is to get the file specified by the user.
This required an update to our main function which takes positional parameters after our
`getopt` options:
```c
// NEW: Process files as specified by the user.
char* file = argv[optind];

if (file == NULL) {
    printf("Specify a file to open.\n");
    exit(1);
}
```

