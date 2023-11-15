// Include necessary headers
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "ctype.h"
using namespace std;

// Declare output file stream
ofstream myfile;

// Function to open the IR file
void openIRFile(){
    myfile.open ("IRcode.txt");
}

// Function to close the IR file
void closeIRFile(){
    myfile.close();
}

// Function to write largest variable information to the IR file
void IRLargestVar(int i){
    myfile << "!LargestVar," << i << "\n";
}

// Function to assign one variable to another in the IR code
void varEqVar(int id1, int id2){
    string tId1 = "T" + to_string(id1 + 1);
    string tId2 = "T" + to_string(id2 + 1);
    myfile << tId1 << " = " << tId2 << "\n";
}

// Function to check if recursion is present and return the corresponding string
string isRecur(int r){
    if(r == 0){
        return "";
    }
    return "R" + to_string(r);
}

// Function to set the register for a parameter
string setParReg(int i){
    return "a" + to_string(i);
}

// Function to set the register for a variable
string setReg(int i){
    return  "T" + to_string(i+1);
}

// Function to assign a number to a variable in the IR code
void varEqNum(int id1, string data){
    myfile << setReg(id1) << " = " << data << "\n";
}

// Function to start an IR binary operation with two variables
void IRBinOpStart(int id1, int id2){
    myfile << "\n" << setReg(id1) << " = " << setReg(id2);
}

// Function to start an IR binary operation with a variable and a number
void IRBinOpStart(int id1, string data){
    myfile << "\n" << setReg(id1) << " = " << data;
}

// Function to add an IR binary operation with two variables
void IRBinOpAdd(string bin, int id1, int id2, int id3){
    myfile << " " << bin << " " << setReg(id1) << "\n";
    myfile << setReg(id2) << " = " << setReg(id3);
}

// Function to add an IR binary operation with a variable and a number
void IRBinOpAdd(string bin, string data, int id2, int id3){
    myfile << " " << bin << " " << data << "\n";
    myfile << setReg(id2) << " = " << setReg(id3);
}

// Function to end an IR binary operation with two variables
void IRBinOpEnd(string bin, int id1, int id2, int id3){
    myfile << " " << bin << " " << setReg(id1) << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n";
}

// Function to end an IR binary operation with a variable and a number
void IRBinOpEnd(string bin, string data, int id2, int id3){
    myfile << " " << bin << " " << data << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n\n";
}

// Function to write a variable to the output in IR
void IRWrite(int id1){
    myfile << "WRITE " << setReg(id1) << "\n";
}

// Function to return a variable in IR
void IRReturn(int id1){
    myfile << "RETURN " << setReg(id1) << "\n\n";
}

// Function to write a newline in IR
void IRWriteLn(){
    myfile << "WRITELN\n\n";
}

// Function to start a new function in IR
void IRStartFunc(string func){
    myfile << "\n" << func << ":\n";
}

// Function to set a parameter in IR
void IRSetParam(int i){
    myfile << setReg(i) << " = " << setParReg(i) << "\n";
}

// Function to jump to a function in IR
void IRJal(string func){
    myfile << "jal " << func << "\n";
}

// Function to return a value from a jal function in IR
void IRJalReturn(int a){
    myfile << setReg(a) << " = v0\n";
}

// Function to implement an if statement in IR with two variables
void IRIfEqVar(int id1, int id2, int f, int r){
    myfile << "beq " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with a variable and a number
void IRIfEqNum(int id1, string data, int f, int r){
    myfile << "beq " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with two variables
void IRIfGrVar(int id1, int id2, int f, int r){
    myfile << "bgt " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with a variable and a number
void IRIfGrNum(int id1, string data, int f, int r){
    myfile << "bgt " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with two variables
void IRIfLeVar(int id1, int id2, int f, int r){
    myfile << "blt " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with a variable and a number
void IRIfLeNum(int id1, string data, int f, int r){
    myfile << "blt " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with two variables
void IRIfGrEqVar(int id1, int id2, int f, int r){
    myfile << "bge " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with a variable and a number
void IRIfGrEqNum(int id1, string data, int f, int r){
    myfile << "bge " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with two variables
void IRIfLeEqVar(int id1, int id2, int f, int r){
    myfile << "ble " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

// Function to implement an if statement in IR with a variable and a number
void IRIfLeEqNum(int id1, string data, int f, int r){
    myfile << "ble " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

// Function to perform a goto at the end of an if statement in IR
void IRIfEndGoto(int f, int r){
    myfile << "b ifEnd" << f << isRecur(r) << "\n";
}

// Function to declare the end of an if statement in IR
void IRIfDecl(int f, int r){
    myfile << "if" << f << isRecur(r) << ":\n";
}

// Function to perform a goto at the end of an else statement in IR
void IRElseEndGoto(int f, int r){
    myfile << "b elseEnd" << f << isRecur(r) << "\n";
}

// Function to declare the end of an else statement in IR
void IRElseEndDecl(int f, int r){
    myfile << "elseEnd" << f << isRecur(r) << ":\n";
}

// Function to declare the end of an if statement in IR
void IRIfEndDecl(int f, int r){
    myfile << "ifEnd" << f << isRecur(r) << ":\n";
}

// Function to perform a jal operation to input a value in IR
void IRJalInput(int a, int in){
    myfile << setParReg(a) << " = " << setReg(in) << "\n";
}

//==============================================================================================================

// Function to optimize the IR code
void optimizeIR()
{
    ifstream ifs;

    // Open the input IR file
    ifs.open("IRcode.txt");
    
    // Variables for line construction
    const int linesize = 100;
    char line[linesize];
    int linecounter = 50; // For future dynamic allocation
    bool flag[linecounter];
    int counter = 0;
    
    // 2D Array to store all lines
    char lines[linecounter][linesize];

    // For constant folding
    char remainder1[linesize];
    char remainder2[linesize];
    char newstring[linesize];
    char newvalue[linesize];
    int value1;
    int value2;

    //// For strength reduction
    int count;
    char linesave[100];

    // For dead code elimination
    char elimvar[2];

    // For constant propagation
    int maxnumsize = 10;

    // Fill "lines" array with lines
    while (ifs.getline(line, linesize, '\n'))
    {
        for (int i = 0; i < linecounter; i++)
        {
            for (int j = 0; j < linesize; j++)
            {
                lines[i][j] = line[j];
            }
        }
        counter++;
    }

    // Constant propagation
    counter = 0;
    for (int i = 0; i < linecounter; i++)
    {
        if (isdigit(lines[i][5]))
        {
            elimvar[0] = lines[i][0];
            elimvar[1] = lines[i][1];
            for (int j = 5; j < linesize; j++)
            {
                remainder1[j] = lines[i][j];
            }
            for (int j = i+1; j < linecounter; j++)
            {
                for (int k = 0; k < linesize; k++)
                {
                    if(lines[j][k] == elimvar[0] && lines[j][k+1] == elimvar[1])
                    {
                        for (int l = k; l < linesize; l++)
                        {
                            lines[j][l + maxnumsize] = lines[j][l];
                            lines[j][l] = ' ';
                            for (int m = 0; m < maxnumsize; m++)
                            {
                                lines[j][l] = remainder1[l];
                            }
                        }
                    }
                }
            }
        }
    }

    // Constant folding
    for (int i = 0; i < linecounter; i++)
    {
        for (int j = 0; i < linesize; i++)
        {
            if (lines[i][j] == '+')
            {
                flag[i] = true;
            }
        }
    }
    for (int i = 0; i < linecounter; i++)
    {
        if (flag[i] == flag[i + 1])
        {
            if (isdigit(lines[i][10]) && isdigit(lines[i + 1][10]))
            {
                for (int j = 10; j < linesize; j++)
                {
                    remainder1[j] = lines[i][j];
                    remainder2[j] = lines[i + 1][j];
                }
                value1 = atoi(remainder1);
                value2 = atoi(remainder2);
                value1 = value1 + value2;
                sprintf(newstring, "%d", value1);
                for (int j = 10; j < linesize; j++)
                {
                    lines[i + 1][j] = newstring[j];
                }
                for (int j = 0; j < linesize; j++)
                {
                    lines[i][j] = ' ';
                }
            }
        }
        flag[i] = 0;
    }

    // Strength reduction
    for (int i = 0; i < linecounter; i++)
    {
        for (int j = 0; i < linesize; i++)
        {
            if (lines[i][j] == '*')
            {
                flag[i] = true;
            }
        }
    }
    for (int i = 0; i < linecounter; i++)
    {
        if (flag[i] == true)
        {
            if (isdigit(lines[i][10]))
            {
                for (int j = 10; j < linesize; j++)
                {
                    remainder1[j] = lines[i][j];
                }
                count = atoi(remainder1);
                for (int j = 0; j < linesize; j++)
                {
                    linesave[j] = lines[i][j];
                }
                if (count >= linecounter - i - 1)
                {
                    for (int j = i; j < linecounter; j++)
                    {
                        for (int k = 0; k < linesize; k++)
                        {
                        }
                        linesave[10] = '+';
                        for (int j = i; j < linecounter; j++)
                        {
                        }
                    }
                }
            }
        }
    }

    // Dead code elimination
    counter = 0;
    for (int i = 0; i < linecounter; i++)
    {
        elimvar[0] = lines[i][0];
        elimvar[1] = lines[i][1];
        for (int j = 0; j < linecounter; j++)
        {
            if (lines[i][j] == elimvar[0] && lines[i][j+1] == elimvar[1])
            {
                counter++;
            }
        }
        if (counter > 1)
        {
            counter = 0;
        }
        else if (counter == 1)
        {
            for (int j = 0; j < linesize; j++)
            {
                lines[i][j] = ' ';
            }
            counter = 0;
        }
    }

    // Write lines to file
    ifs.close();
    
    openIRFile();

    for (int i = 0; i < linecounter; i++)
    {
        for (int j = 0; j < linesize; j++)
        {
            myfile << lines[i][j];
        }
        myfile << "\n";
    }

    closeIRFile();
}
