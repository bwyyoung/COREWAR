	.name "basic"
	.comment "just a basic living prog"

	ld		%0, r10
	st		r1, 6
l:
	live	%21474836481231231231231231231231231230
	zjmp	%:l
