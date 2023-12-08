.data
newline: .asciiz "\n"
out_string0: .asciiz "result:"
.text
#---


addValue:
move $t1, $a0
move $t2, $a1

add $t9, $t2, $t1
move $t3, $t9
move $v0, $t3
jr $ra


main:
li $t4, 30
whileStart0:
bgt $t4, 0, whileCode0
b whileEnd0
whileCode0:
move $a0, $t4
move $a1, $t0
jal addValue
move $t6, $v0

sub $t9, $t4, 5
move $t4, $t9

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, out_string0
syscall
li $v0,1
move $a0, $t6
syscall
b whileStart0
whileEnd0:

#---
# FINISHED

li $v0,10 # call code
syscall # system call
.end main
