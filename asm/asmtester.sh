#!/bin/bash

for i in ../champions/*.s
do
	echo "---------------------------------------"
	echo $i
	rm -rf ft.cor
	rm -rf cp.cor
	./asm $i > ft.cor
	../software/asm $i > cp.cor
	diff <(hexdump -vC ft.cor) <(hexdump -vC cp.cor)
	echo "---------------------------------------"
done
