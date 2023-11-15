.data
newline: .asciiz "\n"
.text
#---


main:
li $t1, 15
li $t2, 12
li $t3, 19
bge $t1, 10, if0
b ifEnd0
if0:
li $v0,1
move $a0, $t1
syscall
ble $t2, 10, if0R1
b ifEnd0R1
if0R1:
li $v0,1
move $a0, $t2
syscall
b elseEnd0R1
ifEnd0R1:
b elseEnd0
ifEnd0:
li $v0,1
move $a0, $t3
syscall
elseEnd0R1:
elseEnd0:

#---
# FINISHED

li $v0,10 # call code
syscall # system call
.end main
