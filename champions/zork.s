.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:jumper, %1
		and r1, %0, r1

jumper:	live %1
		zjmp %:jumper
