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
