	.name "basic"
	.comment "just a basic living prog"

	xor	r1,r2,r3
	xor	:label,%:label,r3
	xor	:label,%0,r3
label:

