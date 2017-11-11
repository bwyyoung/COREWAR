	.name "basic"
	.comment "just a basic living prog"

#start instructions
	ld		%0, r10
	st		r1, 6#commentaire colle!
	ld		%0, r10
#be sure we live
l:		# ninja comment :D
	live	%0		# assure we live
	zjmp	%:l		
test:
#petit commentaire
	ld %0,r10
	#commentaire entre les deux
	st r1,:test
	#un commentaire
	#deux commentaire
