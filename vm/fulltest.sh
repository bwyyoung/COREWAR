#!/bin/bash

i=0
while [ $i -le 16 ]
do
	echo '============================================'
	echo "Verbosity $i"
	# slow
	./differ.sh $i bee_gees
	./differ.sh $i big_feet
	./differ.sh $i mandragore	
	./differ.sh $i meowluigi 	

	#./differ.sh $i champ _ slider2 littlepuppy
	#./differ.sh $i youforkmytralala bigzork zork turtle
	#./differ.sh $i machine-gun fluttershy fluttershy helltrain
	#./differ.sh $i misaka_mikoto turtle Gagnant mortel

	#./differ.sh $i helltrain helltrain helltrain helltrain
	#./differ.sh $i helltrain helltrain helltrain
	#./differ.sh $i helltrain helltrain
	#./differ.sh $i fluttershy fluttershy fluttershy fluttershy
	#./differ.sh $i fluttershy helltrain turtle turtle
	#./differ.sh $i youforkmytralala fluttershy helltrain turtle

	#./differ.sh $i _ _ _ _
	#./differ.sh $i champ champ champ champ
	#./differ.sh $i turtle slider2 mortel littlepuppy
	#./differ.sh $i Gagnant machine-gun fluttershy bigzork
	#./differ.sh $i _honeybadger big_feet corelol champ
	#./differ.sh $i champ gedeon helltrain mortel
	#./differ.sh $i salamahenagalabadoun misaka_mikoto turtle turtle
	#./differ.sh $i misaka_mikoto misaka_mikoto misaka_mikoto misaka_mikoto
	#./differ.sh $i zork
	#./differ.sh $i bigzork
	#./differ.sh $i fluttershy
	#./differ.sh $i helltrain
	#./differ.sh $i turtle
	#./differ.sh $i _			
	#./differ.sh $i champ
	#./differ.sh $i kappa
	#./differ.sh $i marineking		
	#./differ.sh $i misaka_mikoto
	#./differ.sh $i octobre_rouge_v4.2
	#./differ.sh $i rainbow_dash
	#./differ.sh $i thunder
	#./differ.sh $i varimathras
	#./differ.sh $i wall
	#./differ.sh $i _honeybadger
	#./differ.sh $i casimir
	#./differ.sh $i champ
	#./differ.sh $i corelol
	#./differ.sh $i darksasuke
	#./differ.sh $i doge
	#./differ.sh $i dubo
	#./differ.sh $i ex
	#./differ.sh $i gedeon
	#./differ.sh $i jumper 		
	#./differ.sh $i littlepuppy
	#./differ.sh $i live
	#./differ.sh $i loose
	#./differ.sh $i machine-gun
	#./differ.sh $i maxidef
	#./differ.sh $i minus
	#./differ.sh $i mortel
	#./differ.sh $i rainbow_dash
	#./differ.sh $i salamahenagalabadoun
	#./differ.sh $i skynet
	#./differ.sh $i slider2
	#./differ.sh $i terminator
	#./differ.sh $i thunder
	#./differ.sh $i toto
	#./differ.sh $i turtle
	#./differ.sh $i ultimate-surrender
	#./differ.sh $i varimathras
	#./differ.sh $i wall
	#./differ.sh $i youforkmytralala

	((i = i * 2))

	if [[ i -eq 0 ]]
	then
		((i = 1))
	fi
	echo '============================================'
done

