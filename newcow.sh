#!/bin/bash

mkdir c/build

cmake -S ./c -B ./c/build -DCMAKE_C_COMPILER=/usr/bin/gcc
make -C c/build

./c/build/newcow "$@"