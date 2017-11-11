	.name "basic"
	.comment "just a basic living prog"

	ld		%0, r10
	st		r1, 6
	st		r1, :6
6:
	live	%0
	zjmp	%:6
