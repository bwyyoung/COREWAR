l:
	ld		%0, r10
	st		r1, 6
	live	%0
	zjmp	%:l

.name "basic"
.comment "just a basic living prog"
