	.name "basic"
	.comment "just a basic living prog"

l:
	ld		%0, r10
	st		r1, 6
l
toto:
	live	%0
	zjmp	%:l
