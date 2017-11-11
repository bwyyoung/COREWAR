	.name "basic"
	.comment "just a basic living prog"

	ld		%0, r10
	st		r1, :l
	st		r1, -2
	st		r1, 2
l:
	live	%0
	zjmp	%:l
