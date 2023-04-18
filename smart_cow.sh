#!/bin/bash

# Passez le calcul à bc et cowsay le résultat
if [ $# -ne 1 ]; then
  echo "Usage: $0 <sum>"
  exit 1
fi

result=$(echo "$1" | bc -l)

if ((result > 99))
then
  cowsay "Result too long"
  exit 1
fi

cowsay -e $result $1