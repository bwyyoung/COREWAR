	.name "basic"
	.comment "just a basic living prog"

# T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
	or r1, r2, r3
	or r1, %:label, r2
label:	or r1, :label, r2
or :label, %:label, r2
or %:label, r2, r3
