#!/bin/bash

make > /dev/null
rm -rf diff.txt
rm -rf ft.txt
rm -rf cp.txt

path=~/corewar/champions/

./asm $path$1.s > /dev/null
./asm $path$2.s > /dev/null
./asm $path$3.s > /dev/null
./asm $path$4.s > /dev/null

if [ $4 ]
then
	champs="$path$1.cor $path$2.cor $path$3.cor $path$4.cor"
elif [ $3 ]
then
	champs="$path$1.cor $path$2.cor $path$3.cor"
elif [ $2 ]
then
	champs="$path$1.cor $path$2.cor"
elif [ $1 ]
then
	champs="$path$1.cor"
fi

./vm -v 2 $champs | awk '{v[c++]=$0}END{print v[c-2]}' | awk '{print $NF}'
