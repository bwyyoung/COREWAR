	.name "basic"ld		%0, r10
	.comment "just a basic living prog"

	st		r1, 6
l:
	live	%0
	zjmp	%:l
