


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
// Output stream for the generated assembly code

ofstream ASM;
// Counter for generating unique string labels

int stringCo = 0;

// Function to read the intermediate code and generate string labels in the assembly code

void PreASMGen(){
    ifstream IR;
    IR.open ("IRcode.txt");
    string line;
    while(getline(IR, line))
    {   
        if (line.find("!") == 0){
         // Generate string label for out_string

            ASM << "out_string" << stringCo << ": .asciiz " << line.substr(1) << "\n";
            stringCo++;
        }
    }
    IR.close();
}

// Function to open the assembly file and prepare the data section

void openASMFile(){
    ASM.open ("final.asm");
    ASM << ".data\n";
    ASM << "newline: .asciiz \"\\n\"\n";
    PreASMGen();
    ASM << ".text\n";
    ASM << "#---\n\n";
}
// Function to close the assembly file and add the finishing code

void closeASMFile(){

    ASM << "\n#---\n";
    ASM << "# FINISHED\n\n";
  
    ASM << "li $v0,10 # call code\n";
    ASM << "syscall # system call\n";
    ASM << ".end main\n";

    ASM.close();
}
// Function to map register names from intermediate code to MIPS assembly registers

string getRegester(string in){
    string r;
    if(in[0] == 'T'){
        string temp = in.substr(1);
        r = "$t" + temp;
    }
    else if (in[0] == 's') {
        string temp = in.substr(1);
        r = "$s" + temp;
    }else if (in[0] == 'a') {
        string temp = in.substr(1);
        r = "$a" + temp;
    }else if (in[0] == 'v') {
        string temp = in.substr(1);
        r = "$v" + temp;
    }
    else{
        r = in;
    }
    return r;
}
// Functions to generate MIPS assembly code for different intermediate code instructions


void ASMEq(string l){
    string p1 = l.substr(0,l.find(" "));
    string p2 = l.substr(l.find("=")+2);
    cout << "move " << getRegester(p1) << ", " << getRegester(p2) << "\n";
    if(p2[0] == 'T' || p2[0] == 's' || p2[0] == 'a' || p2[0] == 'v'){
        ASM << "move " << getRegester(p1) << ", " << getRegester(p2) << "\n";
    }else{
        ASM << "li " << getRegester(p1) << ", " << getRegester(p2) << "\n";
    }
}

void ASMAdd(string l){
    string p1 = l.substr(0,l.find(" "));
    string p2 = l.substr(l.find("=")+2, l.find(" +")-(l.find("=")+2));
    string p3 = l.substr(l.find("+")+2);

    cout << "add " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
    ASM << "add " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
}

void ASMMult(string l){
    string p1 = l.substr(0,l.find(" "));
    string p2 = l.substr(l.find("=")+2, l.find(" *")-(l.find("=")+2));
    string p3 = l.substr(l.find("*")+2);

    cout << "mul " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
    ASM << "mul " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
}

void ASMMinus(string l){
    string p1 = l.substr(0,l.find(" "));
    string p2 = l.substr(l.find("=")+2, l.find(" -")-(l.find("=")+2));
    string p3 = l.substr(l.find("-")+2);

    cout << "sub " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
    ASM << "sub " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
}

void ASMMinus2(string l){
    string p1 = l.substr(0,l.find(" "));
    string p2 = l.substr(l.find("=")+2, l.find(" -")-(l.find("=")+2));
    string p3 = l.substr(l.find("-")+2);

    cout << "add " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
    ASM << "add " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
}

void ASMDiv(string l){
    string p1 = l.substr(0,l.find(" "));
    string p2 = l.substr(l.find("=")+2, l.find(" /")-(l.find("=")+2));
    string p3 = l.substr(l.find("/")+2);

    cout << "div " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
    ASM << "div " << getRegester(p1) << ", " << getRegester(p2) << ", " << getRegester(p3) << "\n";
}

void ASMWrite(string l){
    string p1 = l.substr(l.find(" ")+1);

    ASM << "li $v0,1\n";
    cout << "move $a0, " << getRegester(p1) << "\n";
    cout << "syscall\n";
    ASM << "move $a0, " << getRegester(p1) << "\n";
    ASM << "syscall\n";
}

void ASMWriteString(string l){
    string p1 = l.substr(l.find(" ")+1);

    ASM << "li $v0, 4\n";
    cout << "la $a0, " << getRegester(p1) << "\n";
    cout << "syscall\n";
    ASM << "la $a0, " << getRegester(p1) << "\n";
    ASM << "syscall\n";
}

void ASMReturn(string l) {
    string p1 = l.substr(l.find(" ") + 1);

    ASM << "move $v0, " << getRegester(p1) << "\n";
    cout << "move $v0, " << getRegester(p1) << "\n";
    cout << "jr $ra\n";
    ASM << "jr $ra\n";
}

void ASMBeq(string l){
    string s = l.substr(4);
    cout << "STINRG  || " << s << "\n";
    string p1 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    string p2 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    cout << "beq " <<  p2 << "\n";
    ASM << "beq " << getRegester(p1) << ", " << getRegester(p2) << ", " << s << "\n";


}

void ASMBge(string l){
    string s = l.substr(4);
    cout << "STINRG  || " << s << "\n";
    string p1 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    string p2 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    cout << "bge " <<  p2 << "\n";
    ASM << "bge " << getRegester(p1) << ", " << getRegester(p2) << ", " << s << "\n";


}

void ASMBle(string l){
    string s = l.substr(4);
    cout << "STINRG  || " << s << "\n";
    string p1 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    string p2 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    cout << "ble " <<  p2 << "\n";
    ASM << "ble " << getRegester(p1) << ", " << getRegester(p2) << ", " << s << "\n";


}

void ASMBgt(string l){
    string s = l.substr(4);
    cout << "STINRG  || " << s << "\n";
    string p1 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    string p2 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    cout << "bgt " <<  p2 << "\n";
    ASM << "bgt " << getRegester(p1) << ", " << getRegester(p2) << ", " << s << "\n";


}

void ASMBlt(string l){
    string s = l.substr(4);
    cout << "STINRG  || " << s << "\n";
    string p1 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    string p2 = s.substr(0,s.find(","));
    s = s.substr(s.find(",") + 2);
    cout << "STINRG  || " << s << "\n";
    cout << "blt " <<  p2 << "\n";
    ASM << "blt " << getRegester(p1) << ", " << getRegester(p2) << ", " << s << "\n";


}

// Function to generate MIPS assembly code by reading intermediate code

void ASMGen(){
    ifstream IR;
    IR.open ("IRcode.txt");
    string line;
    while(getline(IR, line))
    {   
        if(line.find("!") != -1){
            // Skip comments

            
        }else{
        cout << "::" << line << "\n";
        if(line.find("=") != -1){
            if(line.find("*") != -1){
                ASMMult(line);
            }else if(line.find("+") != -1){
                ASMAdd(line);
            }else if(line.find("/") != -1){
                ASMDiv(line);
            }else if(line.find("= -") != -1){
                ASMMinus2(line);
            }else if(line.find("-") != -1){
                ASMMinus(line);
            }else{
                ASMEq(line);
            }
        }
        if(line.find("WRITE") != -1){
            // Handle WRITE instruction
            if(line.find("WRITELN") == -1){
                if(line.find("out_string") == -1){
                    ASMWrite(line);
                }else{
                    ASMWriteString(line);
                }
            }
        }
        if(line == ""){
            ASM << "\n";
        }
        if (line.find(":") != -1) {
           // Handle labels

            cout << line << "\n";
            ASM << line << "\n";
        }
        if (line.find("RETURN") != -1)
        {
            ASMReturn(line);
        }
        if (line.find("jal") != -1)
        {
            ASM << line << "\n";
        }
        if (line.find("WRITELN") != -1)
        {
            ASM << "li $v0, 4\n";
            ASM << "la $a0, newline\n";
            ASM << "syscall\n";
        }
        if (line.find("beq") != -1){
            cout << "::" << line << "\n";
           
            ASMBeq(line);

        }
        if (line.find("bge") != -1){
            ASMBge(line);

        }
        if (line.find("ble") != -1){
            ASMBle(line);
        }
        if (line.find("bgt") != -1){
            ASMBgt(line);
        }
        if (line.find("blt") != -1){
            ASMBlt(line);
        }
        if (line.find("b ") == 0){
            ASM << line << "\n";
        }
        }
    }
}

