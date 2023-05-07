# Projet Cowsay
TODO translate

Dans ce projet, nous apprenons et réimplémentons Cowsay. C'était à l'origine un projet perl
lancé par son auteur dans le but d'apprendre le langage de programmation, ce projet est maintenant
largement non maintenu mais son code source est facilement disponible en ligne, et sa documentation
est disponible via son pages `man`.

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

Cette section contient tout notre code bash, les premiers scripts sont explicites à partir des commentaires tels que
nous n'avons pas ressenti le besoin d'écrire sur la façon dont nous sommes arrivés à leur solution, car ils étaient simples à mettre en œuvre.

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

La suite de Fibonacci est une suite de nombres dans laquelle chaque nombre est la somme des deux nombres qui le précèdent. J
La séquence commence généralement par les chiffres 0 et 1, et les nombres suivants sont calculés en additionnant les deux précédents
Nombres. Ainsi, la suite de Fibonacci commence par 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, etc.

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

`cow_university.sh` était probablement le plus compliqué à mettre en œuvre jusqu'à présent. Calculer si oui ou non un nombre est un
premier n'est pas très facile. Notre approche commence par imprimer 2 comme première entrée, car c'est le seul nombre premier pair, puis il continue par les nombres impairs par la suite à partir de trois jusqu'à `$1`. On vérifie ensuite si le nombre est premier
en passant par tous les diviseurs possibles jusqu'à la moitié de `$1`. Techniquement, il est possible de s'arrêter à sqrt($1) mais cela s'est avéré s'est avéré plutôt difficile à faire, car la comparaison des résultats de l'opération sqrt via bc n'a pas agi comme prévu.

Si nous déterminons qu'il s'agit d'un nombre premier, nous le disons et dormons pendant 1 seconde.

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

`smart_cow` en principe est probablement le plus simple à mettre en œuvre car il existe un
commande unix `bc` qui prend une opération mathématique et calcule le résultat. En fait, nous
ont pu implémenter la fonctionnalité demandée dans le projet enonce avec une seule ligne de code :

```bash
#!/bin/bash
# Cowsay la somme fournie et définissez le résultat pour être les yeux
cowsay -e "$(bc <<< "$1")" "$1"
```

Il y a deux problèmes avec cela, le premier est que si le résultat est supérieur à 100, le résultat dans les yeux est perdu.
Nous pouvons ajouter un cas limite pour cela en remettant les yeux sur "oo" pour les résultats supérieurs à 100, puis simplement
en l'ajoutant à ce que dit la vache.

La seconde est qu'il ne gère pas les expressions mathématiques incorrectes/malformées. Nous pouvons résoudre ce problème
avec les modifications suivantes à smart_cow
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

C'était difficile de penser quoi faire pour crazy_cow, nous ne pouvions penser à rien de particulièrement fou, alors
nous avons décidé d'opter pour quelque chose de compliqué à la place. Nous avons choisi d'écrire un scénario qui
vache dire les paiements mensuels et les intérêts dus pour une hypothèque en utilisant l'amortissement de l'hypothèque
formule:

![](mort_amor_formula.png)

```bash
 #!/bin/bash

# Assurez-vous que nous avons les arguments requis
if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <principal> <interest_rate> <term_in_years>"
    exit 1
fi

# Analyser les arguments de la ligne de commande
principal=$1
tauxInteret=$2
dureeAnnuelle=$3

# Calculer le taux d'intérêt mensuel et le nombre de paiements
tauxInteretMensuel=$(echo "scale=10; $tauxInteret / (12 * 100)" | bc)
nombrePaiements=$(echo "$dureeAnnuelle * 12" | bc)

# Calculer le paiement mensuel
paiementMensuel=$(echo "scale=2; $principal * $tauxInteretMensuel / (1 - (1 + $tauxInteretMensuel)^(-$nombrePaiements))" | bc)

# Calculer le total des intérêts payés
total_interest=$(echo "scale=2; ($paiementMensuel * $nombrePaiements) - $principal" | bc)

# Imprimer les résultats
cowsay "Paiement mensuel: ${paiementMensuel} Total des interets payes : ${total_interest}"
```

Pour des raisons de lisibilité nous avons choisi de nommer les paramètres positionnels, le calcul proprement dit se fait en passant
une expression à bc, un peu comme `smart_cow`.

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

Pour une hypothèque de 300 000 à un taux d'intérêt de 4% pendant 30 ans aura un paiement mensuel de 962 eur, et le client
paiera 46 000 d'intérêts sur la durée du prêt.

## C
### new_cow.c

#### 1. Créer une fonction affiche vache qui affiche simplement une vache sans la bulle de text

```c
#include <stdio.h>

# Affiche une représentation en chaîne fixe d'une vache sans bulle de dialogue
void affiche_vache() {
    # Crée une chaîne qui contient la représentation artistique ascii d'une vache
    # Utilise la concaténation de chaînes littérales.
    char* my_cow =
                "\\   ^__^\n"
                " \\  (oo)\\_______\n"
                "    (__)\\        )\\/\\\n"
                "        ||----w |\n"
                "        ||     ||\n";
    
    # Affiche le littéral de chaîne comme argument.
    printf("%s", my_cow);
}

int main() {
    # Imprime la vache sur STDOUT
    affiche_vache();
    return 0; # Signaler que tout s'est bien passé
}
```

Lors de la mise en œuvre, nous n'avons rencontré qu'un seul problème majeur, en prenant l'exemple de la vache du projet
présentation et en le plaçant comme un littéral dans notre code. Nous avons fini par devoir le retaper et ajouter
les séquences d'échappement appropriées (pour le caractère \ ainsi que pour les retours à la ligne.)

Nous avons disposé le littéral de chaîne en utilisant la concaténation de littéraux de chaîne pour des raisons de lisibilité, bien que
vous pouvez tout aussi bien utiliser une seule ligne et compter sur la fonction d'habillage de texte de votre éditeur de texte.
Au moment de l'exécution, il n'y a aucune différence avec ce que nous pourrions dire.

#### 2. Implémenter diverses options de ligne de commande pour new_cow.c

Nous pouvons implémenter des arguments de ligne de commande en utilisant la fonction `getopt()` de C dans `unistd.h`. Nous faisions
ceci en utilisant une boucle while pour obtenir les valeurs de toutes les options possibles (h,T,e)

```c
int option;
while ((option = getopt(argc, argv, "e:T:h")) != -1) {}
```

La variable d'option ne doit être utilisée dans la boucle qu'en tant qu'itérateur de toutes sortes, chaque indicateur aura
sa propre variable pour stocker son état respectif. La chose importante à noter ici est la chaîne
`"e:T:h"` qui indique à getopt les options à attendre, en particulier 'e' et 'T' qui prennent une valeur
et h qui ne le fait pas (indiqué par la présence de deux-points.)

Cela peut être développé ensuite pour enregistrer les valeurs :
```c
int main(int argc, char* argv[]) {
    int option;
    char* valeurE = NULL;
    char* valeurT = NULL;

    while ((option = getopt(argc, argv, "e:T:h")) != -1) {
        switch (option) {
            // Chaîne d'oeil
            case 'e':
                valeurE = optarg;
                break;

            // Corde de langue
            case 'T':
                valeurT = optarg;
                break;

            // Aide / Instructions d'utilisation.
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

-T pour la chaîne de la langue et un indicateur -h générique sont ce que nous avons choisi de prendre de cowsay
à réimplémenter.

Les principaux changements d'implémentation concernaient l'affiche vache qui ressemble maintenant à ceci :
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
        tongue = "  "; // Deux espaces
    } else if (strlen(tongue) != 2) {
        fprintf(stderr, "Invalid Tongue: %s. Must be exactly 2 characters.", tongue);
        exit(1);
    }

    printf(COW_FORMAT, eyes, tongue);
}
```

C'est également à ce stade que nous avons réalisé que le littéral statique de la vache pouvait être une constante bien nommée "COW_FORMAT" L'implantation de la langue et des yeux était plutôt triviale.

Nous avons imposé le fait que les yeux et la langue doivent être de 2 caractères pour éviter d'avoir à
mettre en œuvre l'habillage du texte. Si les yeux ou la langue manquent, des valeurs par défaut sont fournies :
"oo" pour les yeux ou deux espaces pour la langue (c'est-à-dire pas de langue)

S'ils ne sont pas `NULL` mais pas exactement deux caractères, une erreur est envoyée à STDERR expliquant cela et
sort avec un code d'état différent de zéro pour indiquer une erreur.

Nous avons modifié la chaîne de format de vache pour avoir deux spécificateurs de format "%s" pour chacun les yeux et la langue.
Nous utilisons printf pour remplir les valeurs pour cela.

Afin d'implémenter le menu nous avons ajouté un cas dans notre switch/case pour 'h' qui imprime l'aide
l'information sort alors avec un code d'état 0 :
```c
case 'h':
    printf("Usage: %s -e [v] -T [v] -h\n", argv[0]);
    exit(0);
```

Pas besoin de `break` étant donné qu'il serait inaccessible.

#### 3. Étape technique créative

Nous avons décidé de faire en sorte que la vache ait une hauteur variable en étendant le nombre de lignes de pattes que la vache a
basé sur la valeur du paramètre `-H` à ne pas confondre avec `-h` pour l'aide.

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

Nous avons fait cela en implémentant une fonction `repeat_string` qui prend une chaîne constante `str` et le
nombre de types que vous aimeriez qu'il soit répété `N` et concatène N copies de cette chaîne ensemble
en tant que nouvelle chaîne utilisant une allocation de mémoire dynamique qui est ensuite libérée pour éviter les fuites.

```c
char* repeat_string(const char* str, long N) {
    // Allouer de la mémoire pour la nouvelle chaîne
    int len = (int) strlen(str);
    char* new_str = (char*) malloc((N*len + 1) * sizeof(char));
    if (new_str == NULL) {
        // Si pour une raison quelconque nous ne pouvons pas allouer la mémoire, quittez
        fprintf(stderr, "Error: Failed to allocate memory for new string.\n");
        exit(1);
    }

    // Copiez N copies de la chaîne d'origine dans la nouvelle chaîne
    for (int i = 0; i < N; i++) {
        strcat(new_str, str);
    }

    return new_str;
}
```

Nous l'avons ensuite utilisé avec une nouvelle constante pour faire référence à la ligne de jambe à implémenter
les jambes variables :
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

C'est à ce moment que nous avons remarqué une autre amélioration que nous pouvions apporter.
Plutôt que de définir par défaut valeurH et valeurE sur NULL, nous pourrions simplement faire
leur les valeurs par défaut de "oo" et " " et ignorez la vérification NULL.

Les modifications apportées à la fonction principale sont les suivantes :
```c
int main(int argc, char* argv[]) {
    int option;
    char* valeurE = "oo";
    char* valeurT = "  ";
    long valeurHeight = 1;
    char* endptr; // utilisé dans la conversion str en long
    while ((option = getopt(argc, argv, "e:T:H:h")) != -1) {
        switch (option) {
            // Chaîne d'oeil
            case 'e':
                valeurE = optarg;
                break;

            // Chaîne de langue
            case 'T':
                valeurT = optarg;
                break;

            case 'H':
                valeurHeight = strtol(optarg, &endptr, 10);

                // Si une erreur s'est produite lors de la conversion de la chaîne
                if (*endptr != '\0') {
                    fprintf(stderr, "Error converting %s to a long.\n", optarg);
                    exit(1);
                }
                break;

            // Aide / Instructions d'utilisation.
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

En termes de ce que font les deux fonctions présentées, c'est assez simple.
Ils utilisent des codes d'échappement ANSI pour effectuer des méta-tâches sur l'émulateur de terminal.

- `gotoxy(int x, int y)` prend une coordonnée x et y et la déplace vers les coordonnées spécifiées.
- `update()` exécute deux séquences de code d'échappement. `\33[H` est de ramener le curseur en haut à gauche (`H` pour home)
`\033[J` efface l'écran

Pour cette partie du projet nous avons choisi de mettre en place une « vache qui marche sur la lune », une vache qui marche
à l'envers comme le mouvement Signature de Michael Jackson.

Pour cela, nous avons utilisé update() pour effacer l'écran, et gotoxy() pour changer la position du
vache sur l'écran vers la droite.

Nous avons dû apporter quelques modifications à notre code pour que cela fonctionne.

Tout d'abord, nous avons modifié le COW_FORMAT pour qu'il soit un tableau afin que nous puissions
manipuler chaque ligne de la vache (pour la déplacer sur l'écran)

```c
const char* COW_FORMAT[5] = {
        "       ^__^\n",
        "      (%s)\\_______\n", // Eyes
        "     (__)\\        )\\/\\\n",
        "      %s ||----w |\n", // Tongue
        "%s" // Variable Height
};
```

Et pour la chaîne COW_LEG_LINE, nous en avons également fait un tableau, où chaque
l'élément est une image différente dans l'animation (avant, neutre, arrière)

```c
const char *COW_LEG_LINE[3] = {
    "       ||     ||\n",
    "        ||     ||\n",
    "         ||     ||\n"
};
```

Nous avons ensuite mis à jour `affiche_vache` pour prendre également une position x et y
en tant que variable de cadre qui contrôlera quelle jambe elle affichera.

Nous avons également modifié la façon dont la vache est dessinée pour fonctionner avec le nouveau type de tableau
nous avons fait :
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

Bien qu'il soit possible d'utiliser une boucle pour imprimer la vache, nous avons trouvé que c'était
inutilement compliqué en raison de l'utilisation de spécificateurs de format dans les chaînes
C'est beaucoup plus propre de simplement les imprimer par index et de passer les informations pertinentes
données (yeux, langue ou jambes)

Nous avons ensuite ajouté une boucle sans fin à la fin de notre `main()`

```c
  int frame = 0;
  int x = 50, y = 0;
  while (true) {
      affiche_vache(valeurE, valeurT, valeurHeight, frame, x, y);
      usleep(200000); // Pause de 200 ms
      update(x, y);
      frame++;
      if (frame > 2) {
          frame = 0;
      }
      x += 1;
      y += 1;
  }
```

Cela parcourt les valeurs de x et y et fait déplacer la vache vers la droite
et fait une pause de 200 ms avant de continuer.

##### 5. Reading cow

La première étape pour implémenter la vache de lecture est d'obtenir le fichier spécifié par l'utilisateur.
Cela a nécessité une mise à jour de notre fonction principale qui prend des paramètres de position après notre
Options `getopt` :
```c
// NOUVEAU : Traitez les fichiers comme spécifié par l'utilisateur.
char* file = argv[optind];

if (file == NULL) {
    printf("Specify a file to open.\n");
    exit(1);
}
```

## Annexe

Vous trouverez ici le code source complet de chaque fichier C, ainsi que nos scripts de construction et le fichier CMake.


### CMakeLists.txt

Nous l'avons développé dans CLion et avons utilisé CMakeLists pour gérer nos cibles de construction.

```cmake
cmake_minimum_required(VERSION 3.21)
project(cowsay C)

set(CMAKE_C_STANDARD 11)

add_executable(reading_cow reading_cow.c)
add_executable(newcow new_cow.c)
add_executable(wildcow wildcow.c)
add_executable(cow cow.c) 
```

### Créer des scripts

Plutôt que de devoir compiler et exécuter individuellement chaque script individuel, nous avons écrit des scripts shell wrapper pour chaque fichier C. Voici un exemple pour reading_cow.c

```sh
#!/bin/bash

mkdir c/build

cmake -S ./c -B ./c/build -DCMAKE_C_COMPILER=/usr/bin/gcc
make -C c/build

./c/build/reading_cow "$@"
```

Notre structure de dossiers a été divisée en un sous-dossier 'c' et 'bash' pour garder les choses en ordre, et nous avons géré le code source via Git. Le script bash transmet tous les arguments de ligne de commande au fichier C afin que les options et les arguments positionnels fonctionnent comme prévu.

La seule chose qui a changé entre les différents scripts de construction était le chemin d'accès à l'exécutable, car l'étape de construction construite tous les fichiers C dans `CMakeLists.txt`

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
    char* endptr; // utilisé dans la conversion str en long
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