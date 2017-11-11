	.name "basic"
	.comment "just a basic living prog"

	ld		%"bubu", r10
	st		r1, 6
l:
	live	%0
	zjmp	%:l
