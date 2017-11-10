.name "bit"
.comment ""

ld %100, r3
ld %100, r4
or r3, r4, r5
st r5, 100
ld %-100, r3
ld %100, r4
or r3, r4, r5
st r5, 100
ld %-100, r3
ld %-100, r4
or r3, r4, r5
st r5, 100
ld %100, r3
ld %100, r4
xor r3, r4, r5
st r5, 100
ld %-100, r3
ld %100, r4
xor r3, r4, r5
st r5, 100
ld %-100, r3
ld %-100, r4
xor r3, r4, r5
st r5, 100
ld %-2147483647, r3
ld %-2147483647, r4
xor r3, r4, r5
st r5, 100
ld %2147483647, r3
ld %2147483647, r4
and r3, r4, r5
st r5, 100

