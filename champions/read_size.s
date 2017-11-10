.name "read_size"
.comment ""

ldi 0, %0, r2
lldi 0, %0, r3
sti r2, 100, %0
st r2, 100
sti r3, 160, %0
st r3, 150
ldi 100, %10, r2
sti r2, 200, %0
st r2, 200
ldi -100, %10, r2
sti r2, 300, %0
st r2, 300
ldi -800, %10, r2
sti r2, 400, %0
st r2, 400
ldi 800, %10, r2
sti r2, 500, %0
st r2, 500

