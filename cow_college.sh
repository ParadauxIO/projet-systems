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
cowsay $premierFib
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

