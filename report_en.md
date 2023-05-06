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
  - cow.c
- Appendix
  - CMakeLists.txt
  - Build Scripts
  - new_cow.c
  - wildcow.c
  - reading_cow.c
  - cow.c

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
add_executable(cow cow.c) 
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

### cow.c

TODO