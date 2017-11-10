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

cycles=$( ./get_cycles.sh $2 $3 $4 $5 )

diff <( ./vm -d $cycles $champs) <( ./corewar -d $cycles $champs ) 
