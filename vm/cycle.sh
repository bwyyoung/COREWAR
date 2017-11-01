#!/bin/bash

make
../software/asm ../champions/$1.s

../software/corewar -v 2 ../champions/$1.cor | awk '{v[c++]=$0}END{print v[c-2]}'
echo "============================"
#./vm ../champions/$1.cor
./vm -v 2 ../champions/$1.cor | awk '{v[c++]=$0}END{print v[c-2]}'
