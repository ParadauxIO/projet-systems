#!/bin/bash

# Passez le calcul à bc et cowsay le résultat
if [ $# -ne 1 ]; then
  echo "Usage: $0 <sum>"
  exit 1
fi

result=$(echo "$1" | awk '{ printf "%.10f", $0 }')
eyes=$(printf "%02d" $result)
cowsay -e "$result" "The sum is: $1\nThe result is: $eyes"