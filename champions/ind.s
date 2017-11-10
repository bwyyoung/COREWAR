.name "ind"
.comment "ld (i,r) st (r,i) arth (i,i,r) ldi(i, d, r)"

ld 0, r2
ld -100, r3
ld -1000, r4
ld 1000, r5
st r2, 100
st r2, 200
st r2, 300
st r2, -300
st r2, -1000
st r2, -500
st r2, 500
st r2, 1000
and 0, 0, r2
and -100, 0, r3
and -100, -100, r4
and -70000, 0, r5
and 0, -70000, r6
live %0
st r2, 100
st r3, 200
st r4, 300
st r5, 400
st r6, 500
ldi 0, %0, r2
ldi -100, %0, r3
ldi -100, %0, r4
ldi -70000, %0, r5
ldi 70000, %0, r6
st r2, 100
st r3, 200
st r4, 300
st r5, 400
st r6, 500
sti r1, 70000, %0
sti r1, -70000, %0
sti r1, 70000, %0
sti r1, -70000, %0
sti r1, 100, %0
sti r1, 0, %0
lld 0, r2
lld -100, r3
lld 100, r4
lld 70000, r5
lld -70000, r6
lld 0, r7
st r2, 100
st r3, 200
st r4, 300
st r5, 400
st r6, 500
st r7, 600
lldi 0, %0, r2
lldi -100, %0, r3
lldi 100, %0, r4
lldi 70000, %0, r5
lldi -70000, %0, r6
lldi 0, %0, r7
st r3, 200
st r4, 300
st r5, 400
st r6, 500
st r7, 600
or 70000, 1111, r2
or 0, 70000, r3
or 70000, 70000, r4
or -70000, 0, r5
st r2, 100
st r3, 200
st r4, 300
st r5, 400



