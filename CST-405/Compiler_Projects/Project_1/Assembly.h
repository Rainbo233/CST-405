File * MIPScode;

void initAssemblyFile(){
    MIPScode = fopen("MIPScode.asm", "a");

    fprintf(MIPScode, ".text\n");
    fprintf(MIPScode, "main:\n");
    fprintf(MIPScode, "#---");

}

void emitMIPSAssignment(char * id1, char * id2){

    fprintf(MIPScode, "li $t1,%s\n", id1);
    fprintf(MIPScode, "li $t2,%s\n", id2);
    fprintf(MIPScode, "move $t2,$t1\n");
}

void emitMIPSConstantIntAssignment(char id1[50], char id2[50]){
    fprintf(MIPScode, "li $t0,%s\n", id2);
}

void emitMIPSWriteId(char * id){
    fprintf(MIPScode, "move $a0,%s\n", "$t2");
    fprintf(MIPScode, "%s\n", "syscall");
}

void emitEndOfAssemblyCode(){
    fprintf(MIPScode, "#---\n");
    fprintf(MIPScode, "# Done, terminate program\n\n");
    fprintf(MIPScode, "li $v0,1 # call code for terminate\n");
    fprintf(MIPScode, "syscall # system call\n");
    fprintf(MIPScode, "li $v0,10 # call code\n");
    fprintf(MIPScode,"syscall # system call\n");
    fprintf(MIPScode, ".end main\n");
    
}