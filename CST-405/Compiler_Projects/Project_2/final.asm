.data
newline: .asciiz "\n"
.text
#---


test:
move $t1, $a0
move $t2, $a1

add $s7, $t2, $t1
move $t3, $s7
move $v0, $t3
jr $ra


main:
li $t4, 4
li $t5, 4

div $s7, $t4, $t5
sub $s8, $s7, 2
move $t5, $s8

li $t6, 0
li $t7, 1
li $t8, 2
li $t9, 3
li $s2, 5

add $s7, $s2, $t7
add $s8, $s7, $t8
move $s3, $s8
move $a0, $t4
move $a1, $t5
jal test
move $s4, $v0
li $v0,1
move $a0, $t4
syscall
li $v0, 4
la $a0, newline
syscall

li $v0,1
move $a0, $t5
syscall
li $v0, 4
la $a0, newline
syscall

li $v0,1
move $a0, $s3
syscall
li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, newline
syscall

li $v0,1
move $a0, $s4
syscall

#---
# FINISHED

li $v0,10 # call code
syscall # system call
.end main
