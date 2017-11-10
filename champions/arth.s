.name "arth"
.comment ""

ld %100, r3
ld %100, r4
add r3, r4, r5
st r5, 100
ld %-100, r3
ld %100, r4
add r3, r4, r5
st r5, 100
ld %-100, r3
ld %-100, r4
add r3, r4, r5
st r5, 100
ld %100, r3
ld %100, r4
sub r3, r4, r5
st r5, 100
ld %-100, r3
ld %100, r4
sub r3, r4, r5
st r5, 100
ld %-100, r3
ld %-100, r4
sub r3, r4, r5
st r5, 100
ld %-2147483647, r3
ld %-2147483647, r4
sub r3, r4, r5
st r5, 100
ld %2147483647, r3
ld %2147483647, r4
add r3, r4, r5
st r5, 100
