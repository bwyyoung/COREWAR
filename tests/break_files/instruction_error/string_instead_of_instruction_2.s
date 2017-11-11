	.name "basic"
	.comment "just a basic living prog"

	"hello"		r1, 6
	ld		%0, r10
l:
	live	%0
	zjmp	%:l
