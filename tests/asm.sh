#!/bin/bash
FILES=./ia/*.s
for f in $FILES
do
	./asm $f
done
