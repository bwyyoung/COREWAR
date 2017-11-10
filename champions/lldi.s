.name "lldi"
.comment "check if lldi mods the carry"

lldi %5, %0, r2
lldi %0, %0, r2
zjmp %0
st r2, 100
;lldi 100, %1000, r2
st r2, 200
lldi r2, %1000, r2
st r2, 300
lldi -100, %1000, r2
st r2, 400
lldi -1000, %1000, r2
st r2, 500
lldi %100, %-1000, r2
st r2, 600
lldi %-100, %-1000, r2
st r2, 700
lldi 100, %1000, r2
st r2, 800
lldi 0, %1000, r2
st r2, 900
lldi %100, %1000, r2
st r2, 1000

lldi %100, %1000, r2
st r2, 1000
lldi %100, %1000, r2
st r2, 1200
lldi %100, %1000, r2
st r2, 1300
lldi %100, %1000, r2
st r2, 1400
