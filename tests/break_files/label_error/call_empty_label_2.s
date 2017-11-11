	.name "basic"
	.comment "just a basic living prog"

	ld		%:l, r10
	st		r1, 6
l:
	live	%0
	zjmp	%:
