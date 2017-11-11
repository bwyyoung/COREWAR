	.name "basic"
	.comment "just a basic living prog"

toto:
	ld		%0, r10
	st		r1, 6
l:
l:
	live	%0
	zjmp	%:l
