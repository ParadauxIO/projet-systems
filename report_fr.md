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

#### cow.c

### cow.c
    Cette section nous demandait de faire un jeu Tamagotchi. Vous trouverez ci-dessous ce que nous devions mettre en œuvre et le code correspondant.

#### 1. Réexécutez la routine d'impression de la vache que vous avez configurée précédemment
    Prendre l'état de santé de la vache comme paramètre (par exemple byebyelife=0 pour "décédé"),
    lifesucks=1 pour "ne pas se sentir bien" et liferocks=2 pour "en pleine forme"). afficher
    de la vache sera différent pour chaque état (à vous d'imaginer une représentation significative !).

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

#### 2. Créez les deux variables globales stock et santé, qui sont toutes deux des entiers compris entre 0 et 10 et initialisées à 5.
     Nous fixons également les valeurs de stock et de santé entre 0 et 10.
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

#### 3. créer deux routines stock update() et fitness update()
        Mettez à jour les variables stock et fitness, respectivement. Les deux fonctions prendront comme argument la quantité
        de lunchfood alloué à la vache par le joueur et rendra le montant
        jour en tenant compte de l'évolution aléatoire du niveau d'aptitude de la vache et du cheptel
        (en raison des variables de culture et de digestion). Pour ce faire, nous pouvons utiliser la fonction rand().
        comme suit (pensez à l'initialiser au moins une fois) :

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

#### 4. Boucle qui ne se terminera que lorsque la vache entrera dans l'état byebyelife.
        Dans cette boucle, chaque itération :
         (a) affiche votre vache Tagmagoshi dans son état actuel.
         Le joueur n'a jamais accès à la valeur de la variable fitness
         (sinon le jeu serait inutile), mais l'état de la vache est visible à travers l'affichage de la vache
         (b) affiche l'état de la variable de stock.
         (c) demande ensuite à l'utilisateur d'entrer une quantité de nourriture (inférieure ou égale à
         à la taille du stock de la réserve) à affecter à la vache.
         (d) met à jour les variables du stock et de l'état corporel ainsi que l'état du stock et des vaches.
         (e) incrémente une variable de durée de vie qui compte le nombre de passages à l'intérieur
         de la boucle.

        

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
#### 5. Fonctionnalités supplémentaires
        Nous avons ajouté un système de meilleurs scores qui suit les 5 meilleurs scores les plus élevés dans un fichier scores.txt, en économisant le nom du joueur, la date du score et son classement.
        Nous avons ajouté des événements aléatoires tels que la vache licenciée / promue du travail de la vache, cela a un impact
        leur stock.
        Nous avons également ajouté de petites améliorations dans tout le code telles que la gestion des erreurs pour l'entrée,
        différents messages de fin pour les vaches suralimentées/affamées et le nettoyage et le formatage du terminal.

#### Système de pointage

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

#### Événements aléatoires

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