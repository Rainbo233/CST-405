// file to generate the assembly code in .asm file and show mips in terminal


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ofstream ASM;



void openASMFile(){
    ASM.open ("final.asm");
    ASM << ".data\n";
    ASM << "newline: .asciiz \"\\n\"\n";
    ASM << ".text\n";
    ASM << "#---\n\n";
}

void closeASMFile(){

    ASM << "\n#---\n";
    ASM << "# FINISHED\n\n";
  
    ASM << "li $v0,10 # call code\n";
    ASM << "syscall # system call\n";
    ASM << ".end main\n";

    ASM.close();
}

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

void ASMReturn(string l) {
    string p1 = l.substr(l.find(" ") + 1);

    ASM << "move $v0, " << getRegester(p1) << "\n";
    cout << "move $v0, " << getRegester(p1) << "\n";
    cout << "jr $ra\n";
    ASM << "jr $ra\n";
}


void ASMGen(){
    ifstream IR;
    IR.open ("IRcode.txt");
    string line;
    while(getline(IR, line))
    {   
        cout << "::" << line << "\n";
        if(line.find("=") != -1){
            if(line.find("*") != -1){
                ASMMult(line);
            }else if(line.find("+") != -1){
                ASMAdd(line);
            }else if(line.find("/") != -1){
                ASMDiv(line);
            }else if(line.find("-") != -1){
                ASMMinus(line);
            }else{
                ASMEq(line);
            }
        }
        if(line.find("WRITE") != -1){
            if(line.find("WRITELN") == -1){
                ASMWrite(line);
            }
        }
        if(line == ""){
            ASM << "\n";
        }
        if (line.find(":") != -1) {
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
    }
}

