# Cowsay Project
TODO translate

In this project we learn about and re-implement Cowsay. It was originally a perl project 
started by its author in attempt to learn the programming language, this project is now 
largely unmaintained but its source code is readily available online, and its documentation
is available through its `man` pages.

## Sections

- **Bash**
  - cow_kindergarten.sh
  - cow_primaryschool.sh
  - cow_highschool.sh
  - cow_college.sh
  - cow_university.sh
  - smart_cow.sh
  - crazy_cow.sh
- **C**
  - new_cow.c
  - wildcow.c
  - reading_cow.c
  - tamagoshi_cow.c
- Appendix
  - CMakeLists.txt
  - Build Scripts
  - new_cow.c
  - wildcow.c
  - reading_cow.c
  - tamagoshi_cow.c

## Bash

This section contains all of our bash code, the first few scripts are self-explanatory from the comments such that
we didn't feel the need to write up about how we came to their solution, as they were trivial to implement. 

### cow_kindergarten
```c
#!/bin/bash

# Faites une boucle dans la séquence et demandez à cowsay de lister chaque numéro
for (( i=1; i<=10; i++ )) # 10 est la limite
do
  # Effacer l'écran pour chaque image
  clear

  # Afficher le numéro actuel
  cowsay "$i"

  # Attendez une seconde avant de continuer
  sleep 1
done

clear
cowsay -T "j" 10 
```

### cow_primaryschool

```c
#!/bin/bash

# Assurez-vous que nous avons les arguments requis
if [ $# -ne 1 ]; then
  echo "Usage: $0 <number>"
  exit 1
fi

# Faites une boucle dans la séquence et demandez à cowsay de lister chaque numéro
for (( i=1; (i<=$1); i++ )) # Le premier argument fourni est la limite
do
  # Effacer l'écran pour chaque image
  clear

  # Afficher le numéro actuel
  cowsay "$i"

  # Attendez une seconde avant de continuer
  sleep 1
done

# Montrer à nouveau le dernier carré avec une langue
lastI=$((i - 1))
clear
cowsay -T "j" $lastI 
```

### cow_highschool

```c
#!/bin/bash

# Assurez-vous que nous avons les arguments requis
if [ $# -ne 1 ]; then
  echo "Usage: $0 <number>"
  exit 1
fi

# Faites une boucle dans la séquence et demandez à cowsay de lister chaque numéro
for (( i=1; (i <= $1); i++ ))  # Le premier argument fourni est la limite
do
  # Effacer l'écran pour chaque image
  clear

  # Afficher le numéro actuel
  cowsay $((i*i)) # Calculer le carré parfait

  # Attendez une seconde avant de continuer
  sleep 1
done
 
```

### cow_college

The Fibonacci sequence is a sequence of numbers in which each number is the sum of the two numbers before it. T
he sequence usually starts with the numbers 0 and 1, and the following numbers are calculated by adding the previous two
numbers. So the Fibonacci sequence starts with 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, etc.

```bash
#!/bin/bash

# Assurez-vous que nous avons les arguments requis
if [ $# -ne 1 ]; then
  echo "Usage: $0 <number>"
  exit 1
fi

# Définir les deux premiers nombres de Fibonacci
premierFib=0
secondeFib=1

# Donnez à Cowsay la première valeur et attendez
clear
cowsay "$premierFib "
sleep 1

# boucle sur les nombres de Fibonacci inférieurs à le premier argument
while [ $secondeFib -lt "$1" ]; do
  # Effacer l'écran pour chaque image
  clear

  # Afficher le numéro actuel
  cowsay $secondeFib

  # Maintenez temporairement le nombre de Fibonacci précédent
  temp=$premierFib

  # Remplacez le nombre Fibonacci précédent par le premier emplacement
  premierFib=$secondeFib

  # Calculer le prochain nombre de Fibonacci
  secondeFib=$((temp + secondeFib))

  # Attendez une seconde avant de continuer
  sleep 1
done
```

### cow_university

`cow_university.sh` was probably the most complicated to implement thus far. Calculating whether or not a number is a 
prime isn't very easy. Our approach begins by printing 2 as the first entry, as it's the only even prime then it goes 
through the odd numbers thereafter starting at three up until `$1`. We then check to see if the number is a prime
by going through all possible divisors up to half of `$1`. Technically it is possible to stop at sqrt($1) but this turned
out to be rather difficult to do, as comparing the results of the sqrt operation via bc wasn't acting as expected.

If we determine it is a prime we cowsay it and sleep for 1 second.

```bash
#!/bin/bash

# Assurez-vous que nous avons les arguments requis
if [ $# -ne 1 ]; then
  echo "Usage: $0 <number>"
  exit 1
fi

# Donne à cowsay 2 puisque c'est le seul nombre premier pair
clear
cowsay 2
sleep 1

# Boucle sur les nombres impairs inférieurs à la limite
for ((i=3; i<=$1; i+=2))
do
    # Vérifie s'il est premier en le divisant par des nombres impairs jusqu'à sa racine carrée.
    # Si le nombre est divisible par l'un de ces nombres impairs, il n'est pas premier et le
    # script passe au nombre suivant
    est_premier=true
    for ((j=3; j<=i/2; j+=2))
    do
        if [ $((i%j)) -eq 0 ]
        then
            est_premier=false
            break
        fi
    done
    if $est_premier
    then
        # Effacer l'écran pour chaque image
        clear
        # Afficher le numéro actuel
        cowsay "$i"

        # Attendez une seconde avant de continuer
        sleep 1
    fi
done
```

### smart_cow

`smart_cow` in principal is probably the easiest to implement as there is a readily available 
unix command `bc` which takes a mathematical operation and computes the result. In fact, we
were able to implement the functionality requested in the projet enonce with one line of code: 

```bash
#!/bin/bash
# Cowsay the provided sum and set the result to be the eyes
cowsay -e "$(bc <<< "$1")" "$1"
```

There's two problems with this, the first is that if the result is over 100 then the result in the eyes is lost.
We can add an edge case for this by reverting the eyes to 'oo' for results over 100 then simply
adding it to what the cow is saying. 

The second is that it doesn't handle incorrect/malformed mathematical expressions. We can fix this
with the following modifications to smart_cow
```bash 
#!/bin/bash
if ! result=$(bc <<< "$1"); then
  echo "Invalid sum"
  exit
fi

if [ "$result" -gt 99 ]; then
    # If the result is greater than 99, add the result to what the cow is saying
    cowsay "Expression: $1 Result: $result"
else
      cowsay -e " $result" "$1"
fi
```

```bash
paradaux@Rians-MacBook-Pro bash % ./smart_cow.sh '3 + 11'
 ________ 
< 3 + 11 >
 -------- 
        \   ^__^
         \  ( 1)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```

### crazy_cow

It was hard to think what to do for crazy_cow, we couldn't think of anything particularly crazy, so
we decided to go for something complicated instead. We chose to write a script which would
cow say the monthly payments and interest due for a Mortgage by using the mortgage amortisation
formula:

![](mort_amor_formula.png)

```bash
 #!/bin/bash

# Assurez-vous que nous avons les arguments requis
if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <principal> <interest_rate> <term_in_years>"
    exit 1
fi

# Parse command line arguments
principal=$1
tauxInteret=$2
dureeAnnuelle=$3

# Calculate monthly interest rate and number of payments
tauxInteretMensuel=$(echo "scale=10; $tauxInteret / (12 * 100)" | bc)
nombrePaiements=$(echo "$dureeAnnuelle * 12" | bc)

# Calculate monthly payment
paiementMensuel=$(echo "scale=2; $principal * $tauxInteretMensuel / (1 - (1 + $tauxInteretMensuel)^(-$nombrePaiements))" | bc)

# Calculate total interest paid
total_interest=$(echo "scale=2; ($paiementMensuel * $nombrePaiements) - $principal" | bc)

# Print results
cowsay "Paiement mensuel: ${paiementMensuel} Total des interets payes : ${total_interest}"
```

For the purposes of readability we chose to name the positional parameters, the actual calculation is handled by passing
an expression to bc, much like `smart_cow`.

```bash
paradaux@Rians-MacBook-Pro bash % ./crazy_cow.sh 300000 1.04 30
 ____________________________________ 
/ Paiement mensuel: 962.96 Total des \
\ interets payes : 46665.60          /
 ------------------------------------ 
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```

For a mortgage of 300,000 at an interest rate of 4% for 30 years will have a monthly payment of 962 eur, and the client
will pay 46,000 in interest over the term of the loan.

## C
### new_cow.c

#### 1. Créer une fonction affiche vache qui affiche simplement une vache sans la bulle de text

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

#### 2. Implement various command-line options for new_cow.c

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

#### 3. Creative technical step

We decided to make the cow have a variable height by extending the amount of leg lines the cow has
based on the value of the parameter `-H` not to be confused by `-h` for help.

```bash
$ newcow -e hi -H 5
```

```text
paradaux@Rians-MacBook-Pro projet-systems % ./newcow.sh -H 6 
       ^__^
      (oo)\_______
     (__)\        )\/\
         ||----w |
         ||     ||
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

#### 4. gotoxy / update

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

##### 5. Reading cow

The first step is to take the file path provided by the user.
```c
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
```

We have basic error handling to see if the file exists at the path provided, and we initialise some variables
for later.

We also have a `message` variable which is a string of length 100 which will store the full string of what has
been read in. 
```c
char* message = (char*) malloc(100 * sizeof(char));
```

Which we initialise to being the empty string: 
```c
strcpy(message, "");
```

Then it's just a matter of looping over every character in the file at the path provided until we reach the end
of the file (`EOF`)
```c
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
```

For every character in the file we add it to the message string, and increment the variable which tracks the last
used index. Then we split the message into multiple substrings (an array of strings, which is freed later)

This is then drawn in drawThoughtBox which takes the length of the message and then the array of each line in the 
box. It then draws the cow with regular eyes, the tongue of the current character and a height of 1.

```bash
 _________
/ bonj     \
 ---------
       ^__^
      (oo)\_______
     (__)\        )\/\
      o  ||----w |
         ||     ||
paradaux@Rians-MacBook-Pro p
```

For this we implemented a substrings function which takes a string which is too long to fit into one line and splits
it across multiple lines. 
```c
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
```

We also defined a drawThoughtBox function which mimics the thought box that cowsay implements:
```c
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
```

It uses a get_chars function (defined below) to get a particular number of characters repeated. 
```c
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
```

We made sure to free memory any time we used malloc.

### tamagoshi_cow.c
This section asked us to make a Tamagotchi game. Below is what we were required to implement and the relevant code.

#### 1. Re-run the print cow routine you set up earlier
Take the cow's state of health as a parameter (for example byebyelife=0 for "deceased"),
lifesucks=1 for "not feeling well" and liferocks=2 for "in great shape"). display
of the cow will be different for each state (it's up to you to imagine a meaningful representation!).

```c
// Cow ASCII art
const char* COW_FORMAT =
        "       ^__^\n"
        "      (%s)\\_______\n" // Eyes
        "     (__)\\        )\\/\\\n"
        "      %s ||----w |\n" // Tongue
        "         ||     ||\n";
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
```

#### 2. Create the two global variables stock and health, both of which are integers between 0 and 10 and initialized to 5.
We also clamp the values of stock and health to be between 0 and 10.

```c
// Min - Max food stock levels
#define MIN_STOCK 0
#define MAX_STOCK 10

// Cow health levels
#define STARVING 0
#define OVERFED 10

int main() {
    // Stores current state of the cow
    int cow_state = LIFEROCKS;

    // Represents its overall health, not to be disclosed to the user
    int cow_health = 5;

    int stock = 5;
    ../
}
```

#### 3. create two routines stock update() and fitness update() 

Update the variables stock and fitness, respectively. Both functions will take as argument the quantity
of lunchfood allocated to the cow by the player and will return the amount day taking into account the random evolution
of the level of fitness of the cow and the stock (due to crop and digestion variables). To do this, we can use the 
rand() function. as follows (remember to initialize it at least once):
```c
        //function to generate a random number within the given range
        int rand_range(int lower, int upper) {
        // scale and shift the value to the desired range
        return lower + rand() % (upper - lower + 1);
        }
        
        // Seed the random number generator with current time
        srand(time(NULL));

        // Generate random digestion value
        int digestion = rand_range(-3, 0);

        // Update cow's health and stock levels based on food_given and digestion
        cow_health += food_given + digestion;
        stock -= food_given;

        // Generate random crop value
        int crop = rand_range(-3, 3);

        // Update stock level based on crop
        stock += crop;
```

#### 4. Loop that will only terminate when the cow enters the byebyelife state. 
In this loop, each iteration:
1. displays your Tagmagoshi cow in its current state.
The player never has access to the value of the fitness variable
(otherwise the game would be useless), but the cow's state is visible through the cow's display
2. displays the status of the stock variable.
3. then asks the user to enter an amount of food (less than or equal to
to the stock size of the reserve) to be allocated to the cow.
4. updates stock and body condition variables as well as stock and cow status.
5. increments a lifetime variable that counts the number of passes inside of the loop.

```c
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

        printf("Crop: %d\n", crop);
        printf("Digestion: %d\n", digestion);
        printf("Cow's health level: %d\n", cow_health);

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
```

#### 5. Extra features
We added a highscore system that tracks the top 5 highest scores in a scores.txt file, saving
player name, date of score and their ranking.

We added random events such as the cow being fired/promoted from the cow job, this impacts
their stock. 

We also added small improvements throughout the code such as error handling for input,
different end messages for overfeeding/starving cows and clearing and formatting the terminal.

#### Score system

```c
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
```

#### Random events

```c
        // Random events
        #define COW_JOB_FIRING 0
        #define COW_JOB_PROMOTION 1
        
        // 25% chance of firing, 25% chance of promotion, arbitrary choice of values
        const int EVENT_PROBABILITIES[] = {25, 25};
        
        // Your cow got fired from their job
        if (rand_range(0, 100) < EVENT_PROBABILITIES[COW_JOB_FIRING]) {
            sprintf(event_message, "Oh no! You've been fired from your cow job at the cow factory, lose stock!\n");
            stock -= (rand_range(1, 3));

        // Your cow got a promotion at their job
        } else if (rand_range(0, 100) < EVENT_PROBABILITIES[COW_JOB_PROMOTION]) {
            sprintf(event_message, "Woohoo! You've been promoted at your cow job, gain stock!\n");
            stock += (rand_range(1, 3));
        }
```


## Appendex

Here you can find the full source code for each C file, as well as our build scripts and CMake file.

### CMakeLists.txt

We developed this in CLion and used CMakeLists to manage our build targets.

```cmake
cmake_minimum_required(VERSION 3.21)
project(cowsay C)

set(CMAKE_C_STANDARD 11)

add_executable(reading_cow reading_cow.c)
add_executable(newcow new_cow.c)
add_executable(wildcow wildcow.c)
add_executable(tamagoshi_cow tamagoshi_cow.c)
```

### Build scripts

Rather than having to individually compile and run each individual script we wrote wrapper shell scripts for each C file.
Here is an example for reading_cow.c

```sh
#!/bin/bash

mkdir c/build

cmake -S ./c -B ./c/build -DCMAKE_C_COMPILER=/usr/bin/gcc
make -C c/build

./c/build/reading_cow "$@"
```

Our folder structure was split into a 'c' and 'bash' sub-folder to keep things tidy, and we managed the source code via
Git. The bash script passes all command line arguments to the C file so the options and positional arguments would work
as expected.

The only thing that changed between the different build scripts was the path to the executable, as the build step built
all of the C files in `CMakeLists.txt`

### new_cow.c
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define true 1

const char* COW_FORMAT =
        "       ^__^\n"
        "      (%s)\\_______\n" // Eyes
        "     (__)\\        )\\/\\\n"
        "      %s ||----w |\n" // Tongue
        "%s"; // Variable Height

const char *COW_LEG_LINE =
    "         ||     ||\n";

const int MAX_LINE_LENGTH = 100;

char* repeat_string(const char* str, long N);
void affiche_vache(char* eyes, char* tongue, long height);

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
```

### reading_cow.c

```c
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
```

### wildcow.c

```c
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
void affiche_vache(char* eyes, char* tongue, long height, int frame, int x, int y);
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
}

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

void update() {
    printf ("\033[H\033[J");
}
```

### tamagoshi_cow.c
```c
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

        printf("Crop: %d\n", crop);
        printf("Digestion: %d\n", digestion);
        printf("Cow's health level: %d\n", cow_health);

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
```