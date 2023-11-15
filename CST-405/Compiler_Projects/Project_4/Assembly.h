#include <stdio.h>

// Global variable to store the MIPS assembly code file pointer
File *MIPScode;

// Function to initialize the MIPS assembly file
void initAssemblyFile() {
    MIPScode = fopen("MIPScode.asm", "a");

    // Initialize the text section
    fprintf(MIPScode, ".text\n");
    
    // Define the main function
    fprintf(MIPScode, "main:\n");
    
    // Comment to separate sections
    fprintf(MIPScode, "#---");
}

// Function to emit MIPS code for assignment between two identifiers
void emitMIPSAssignment(char *id1, char *id2) {
    // Load the value of id1 into $t1
    fprintf(MIPScode, "li $t1,%s\n", id1);
    
    // Load the value of id2 into $t2
    fprintf(MIPScode, "li $t2,%s\n", id2);
    
    // Move the value from $t1 to $t2
    fprintf(MIPScode, "move $t2,$t1\n");
}

// Function to emit MIPS code for assignment of a constant integer to an identifier
void emitMIPSConstantIntAssignment(char id1[50], char id2[50]) {
    // Load the constant integer value into $t0
    fprintf(MIPScode, "li $t0,%s\n", id2);
}

// Function to emit MIPS code for writing the value of an identifier
void emitMIPSWriteId(char *id) {
    // Move the value of the identifier to $a0 (for syscall)
    fprintf(MIPScode, "move $a0,%s\n", "$t2");
    
    // System call for writing the value
    fprintf(MIPScode, "%s\n", "syscall");
}

// Function to emit the end of the MIPS assembly code
void emitEndOfAssemblyCode() {
    // Comment to separate sections
    fprintf(MIPScode, "#---\n");
    
    // Comment for the end of the program
    fprintf(MIPScode, "# Done, terminate program\n\n");
    
    // System calls to terminate the program
    fprintf(MIPScode, "li $v0,1 # call code for terminate\n");
    fprintf(MIPScode, "syscall # system call\n");
    fprintf(MIPScode, "li $v0,10 # call code\n");
    fprintf(MIPScode, "syscall # system call\n");
    
    // End of the main function
    fprintf(MIPScode, ".end main\n");
}
