.name "basic"
.comment "just a basic living prog"

	sub		r16, r16, r16
	st		r1, 6
l:
	live	%0
	zjmp	%:l
