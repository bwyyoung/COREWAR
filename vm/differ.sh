#!/bin/bash

make > /dev/null
rm -rf diff.txt
rm -rf ft.txt
rm -rf cp.txt

path=~/corewar/champions/

./asm $path$2.s > /dev/null
./asm $path$3.s > /dev/null
./asm $path$4.s > /dev/null
./asm $path$5.s > /dev/null

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

echo "---------------------------------------"
echo "Verbosity $1"
echo $2
echo $3
echo $4
echo $5

if [[ $(diff <(./corewar -v $1 $champs) <(../software/corewar -v $1 $champs )) ]]
then
	echo "			Error"
else
	echo "			OK"
fi
echo "---------------------------------------"
