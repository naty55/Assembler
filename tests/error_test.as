;Test every line has an error
;Label name is a keyword
mov: .data 1
bne: .string "hello"
not: clr @r2
.entry Label, mov, not
.extern Label3, mov, not
.extern !ex_label

;Invalid param type 
mov @r1, 1
add @r1, 1
sub @r1, 1
not 0
clr 0
lea @r2, 1
lea Label,  1
lea 1, 1
inc 2
dec 1
jmp 1
bne 1
red -1
jsr 8

;Missing parameter
mov 1,
mov 1
not 
cmp 5,

; unkonwn operation
stp
doit
func Label, @r3

;Invalid string 
.string "Hello
.string Hello"

;Invalid data
.data 6, A, -222-2, 6*9,0

;Invalid register
mov 5, @r8
mov 5, @e2
mov 5, @r2e

;Invalid label name
!label: mov 5, @r7
reallyreallyreallyreallyreallylonglabellabelname: mov 5, @r7
;Size 32 
longlonglonglonglonglonglabel11:mov 5, @r7
lbel_with_spcae : mov 5, @r7
4lanel: stop

;



