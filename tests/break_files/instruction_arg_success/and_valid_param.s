	.name "basic"
	.comment "just a basic living prog"

# T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
	and r1, r2, r3
	and r1, %:label, r2
label:	and r1, :label, r2
and 0, %:label, r2
and %:label, r2, r3
