READLOOP: cmp @r1, -1
bne AFTERLOOP
jsr READINPUT
jmp READLOOP
READINPUT: red @r1
prn @r1
rts
AFTERLOOP: stop
DATA: .data 10000