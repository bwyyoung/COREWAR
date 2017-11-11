	.name "basic"
	.comment "just a basic living prog"

	ld		%0, r10
	st		r1, 6
a: b: c: l: 
	live	%0
	zjmp	%:l
