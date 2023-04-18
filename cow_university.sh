#!/bin/bash

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