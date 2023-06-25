MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
mcro m1
sub @r1, @r4
bne END
endmcro
prn -5
mcro forrrr
inc @r2
mov K,@r1
endmcro
bne LOOP

;comment
m1
L1: inc K
bne LOOP
END: stop
forrrr
STR: .string “abcdef”
m1   
 forrrr
LENGTH: .data 6,-9,15
K: .data 22