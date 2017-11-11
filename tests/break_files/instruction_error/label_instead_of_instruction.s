	.name "basic"
	.comment "just a basic living prog"

	ld		%0, r10
	%:l		r1, 6
l:
	live	%0
	zjmp	%:l
