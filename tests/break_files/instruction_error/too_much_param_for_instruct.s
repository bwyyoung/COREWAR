	.name "basic"
	.comment "just a basic living prog"

	ld		%0, r10
	st		r1, 6
#too much param here
	sti		r1, r2, r3, r4
l:
	live	%0
	zjmp	%:l
