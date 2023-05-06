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
