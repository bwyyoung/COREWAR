#!/bin/bash

make
rm -rf diff.txt
rm -rf ft.txt
rm -rf cp.txt

path=~/corewar/champions/

./asm $path$2.s
./asm $path$3.s
./asm $path$4.s
./asm $path$5.s

if [ $5 ]
then
	champs="$path$2.cor $path$3.cor $path$4.cor $path$5.cor"
elif [ $4 ]
then
	champs="$path$2.cor $path$3.cor $path$4.cor"
elif [ $3 ]
then
	champs="$path$2.cor $path$3.cor"
elif [ $2 ]
then
	champs="$path$2.cor"
fi
./corewar -v $1 $champs > ft.txt
../software/corewar -v $1 $champs > cp.txt 

diff ft.txt cp.txt
