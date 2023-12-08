// Define a file pointer for the MIPS assembly code file
File * MIPScode;

// Initialize the MIPS assembly file
void initAssemblyFile() {
    // Open the file "MIPScode.asm" for appending
    MIPScode = fopen("MIPScode.asm", "a");

    // Start the text section
    fprintf(MIPScode, ".text\n");
    // Define the main label
    fprintf(MIPScode, "main:\n");
    // Add a comment section to be filled in later
    fprintf(MIPScode, "#---\n");
}

// Emit MIPS instructions for an assignment operation
void emitMIPSAssignment(char * id1, char * id2) {
    // Load the value of id1 into register $t1
    fprintf(MIPScode, "li $t1,%s\n", id1);
    // Load the value of id2 into register $t2
    fprintf(MIPScode, "li $t2,%s\n", id2);
    // Move the value in $t1 to $t2
    fprintf(MIPScode, "move $t2,$t1\n");
}

// Emit MIPS instructions for assigning a constant integer value
void emitMIPSConstantIntAssignment(char id1[50], char id2[50]) {
    // Load the constant integer value into register $t0
    fprintf(MIPScode, "li $t0,%s\n", id2);
}

// Emit MIPS instructions for writing the value of an identifier
void emitMIPSWriteId(char * id) {
    // Move the value in $t2 to $a0 (for printing)
    fprintf(MIPScode, "move $a0,%s\n", "$t2");
    // Perform a syscall to print the value
    fprintf(MIPScode, "%s\n", "syscall");
}

// Emit MIPS instructions for the end of the assembly code
void emitEndOfAssemblyCode() {
    // Add a comment section to indicate the end of the code
    fprintf(MIPScode, "#---\n");
    // Add comments for termination and system call
    fprintf(MIPScode, "# Done, terminate program\n\n");
    fprintf(MIPScode, "li $v0,1 # call code for terminate\n");
    fprintf(MIPScode, "syscall # system call\n");
    fprintf(MIPScode, "li $v0,10 # call code\n");
    fprintf(MIPScode, "syscall # system call\n");
    // End the main section
    fprintf(MIPScode, ".end main\n");
}
