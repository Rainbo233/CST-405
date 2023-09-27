/*
Arrays
local vars
functions
Read
WriteLn


*/


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ofstream ASM;



void openASMFile(){
    ASM.open ("final.asm");

    ASM << ".text\n";
    ASM << "main:\n";
    ASM << "#---\n\n";
}

void closeASMFile(){

    ASM << "\n#---\n";
    ASM << "# FINISHED\n\n";
    //ASM << "li $v0,1 # call code for terminate\n";
    //ASM << "syscall # system call\n";
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
    }else{
        r = in;
    }
    return r;
}

void ASMEq(string l){
    string p1 = l.substr(0,l.find(" "));
    string p2 = l.substr(l.find("=")+2);
    cout << "move " << getRegester(p1) << ", " << getRegester(p2) << "\n";
    if(p2[0] == 'T'){
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

void ASMWrite(string l){
    string p1 = l.substr(l.find(" ")+1);

    ASM << "li $v0,1\n";
    cout << "move $a0, " << getRegester(p1) << "\n";
    cout << "syscall\n";
    ASM << "move $a0, " << getRegester(p1) << "\n";
    ASM << "syscall\n";
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
            }else{
                ASMEq(line);
            }
        }
        if(line.find("WRITE") != -1){
            ASMWrite(line);
        }
        if(line == ""){
            ASM << "\n";
        }
    }
}

