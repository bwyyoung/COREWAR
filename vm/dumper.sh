#!/bin/bash

make
../software/asm ../champions/$1.s
./vm -d $2 ../champions/$1.cor > ft
../software/corewar -d $2 ../champions/$1.cor > cp
diff ft cp
