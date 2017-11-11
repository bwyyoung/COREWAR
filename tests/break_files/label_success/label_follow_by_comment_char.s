	.name "basic"
	.comment "just a basic living prog"

toto:

#hop comment after label

titi:
		#comment :O
	ld		%0, r10
	st		r1, 6
l:  #this is a comment after label :D
	live	%0
	zjmp	%:l
