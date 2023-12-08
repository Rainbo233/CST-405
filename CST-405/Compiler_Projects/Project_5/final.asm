.data
newline: .asciiz "\n"
out_string0: .asciiz "result:"
out_string1: .asciiz "NoChange"
.text
#---


addValue:
move $t1, $a0
move $t2, $a1

add $s0, $t2, $t1
move $t3, $s0
move $v0, $t3
jr $ra


main:
li $t4, 20
add $t5, -5, 
bgt $t4, 0, if0
b ifEnd0
if0:
move $a0, $t4
move $a1, $t5
jal addValue
move $t7, $v0
li $v0, 4
la $a0, out_string0
syscall
li $v0,1
move $a0, $t7
syscall
b elseEnd0
ifEnd0:
li $v0, 4
la $a0, out_string1
syscall
elseEnd0:

#---
# FINISHED

li $v0,10 # call code
syscall # system call
.end main
