#!/bin/bash

mkdir build
cd build || exit

cmake -S ../ -B .
make

./newcow "$@"