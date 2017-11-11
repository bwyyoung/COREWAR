.name "blackhole"
.comment "?"

	ld		%1, r16
	st		r1, 6
live:
	live	%0
	zjmp	%:live
	st		r15, -12
	st		r15, -23
	ld		%190057742, r11				# r11 = 0x0b540d0e (sti r13 r14 ..)
	ld		%269090305, r12				# r12 = 0x1009fe01 (.. r16 zjmp %-511)
pc_1a:
	fork	%:pc_2a
	st		r1, 6
	live	%0
	fork	%:pc_1b
	ld		%190057743, r13				# r13 = 0x0b540d0f (sti r13 r15 ..)
	ld		%-506, r14
	ld		%-24, r15
	ld		%0, r16
	zjmp	%:exit
pc_1b:
	ld		%269090787, r13				# r13 = 0x1009ffe3 (.. r16 zjmp %-29)
	ld		%-502, r14
	ld		%-20, r15
	ld		%0, r16
	zjmp	%:exit
pc_2a:
	st		r1, 6
	live	%0
	fork	%:pc_2b
	ldi		%:live, %0,	r13				# r13 = 0x01?????? (live ?? ?? ?? ..)
	ld		%12, r14
	ld		%-492, r15
	ld		%0, r16
	ld		%0, r1
	zjmp	%:exit
pc_2b:
	ldi		%:live, %4, r13				# r13 = 0x??09fffb (.. ?? zjmp %-5)
	ld		%12, r14
	ld		%-492, r15
	ld		%4, r16
	ld		%0, r1
	zjmp	%:exit
exit:
	st		r11, -491
	st		r12, -492
	st		r1, 6
	live	%0
	zjmp	%-511
