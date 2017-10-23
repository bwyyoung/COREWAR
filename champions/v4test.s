.name "verbosity 4 tester"
.comment ""

zjmp	%50
live	%20
ld	%20, r2
st	r1, 100
add	r1, r2, r3
sub	r1, r2, r4
and	r1, r3, r5
or	10, r4, r6
xor	%10, 5, r7
ldi	r1, %10, r8
sti	r9, r8, r2
fork	%20
lld	%20, r10
lldi	r9, r2, r11
lfork	%30
aff	r3

