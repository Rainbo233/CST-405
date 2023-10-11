.text
main:
#---

li $t1, 100
li $t2, 25

add $t4, $t1, $t2
add $t5, $t4, 4
move $t3, $t5

li $v0,1
move $a0, $t3
syscall

#---
# FINISHED

li $v0,10 # call code
syscall # system call
.end main
