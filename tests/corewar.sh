#!/bin/bash
FILES=./ia/*.cor
for f in $FILES
do
	./corewar $1 $f | grep 'won'
	./corewar $f $1 | grep 'won'
done
