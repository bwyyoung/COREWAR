#!/bin/bash

path=../champions/vm_errors/

make > /dev/null
for i in $path*.s
do
	./asm $i
done

for i in $path*.cor
do
	echo "------------------------------------------"
	echo $i
	./vm $i
	echo "========================="
	./corewar $i
	#diff <(./vm $i -a) <(./corewar $i -a)
	echo "------------------------------------------"
done
