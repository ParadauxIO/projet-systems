#!/bin/bash

mkdir build
cd build || exit

cmake -S ../ -B .
make

./cowsay "This is a string that needs to be split into substrings of 39 characters or less." -file ../cows/dead_cow.cow
./cowsay "This is a string that needs to be split into two different lines" -file ../cows/happy_cow.cow
./cowsay "This is a short string" -file ../cows/default.cow # Not executing in the same dir, have to specify default path