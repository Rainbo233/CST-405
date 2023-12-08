


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "ctype.h"
using namespace std;
// Global ofstream object for writing Intermediate Representation (IR) code

ofstream myfile;
// Function to open the IR file
void openIRFile(){
    myfile.open ("IRcode.txt");
}
// Function to close the IR file
void closeIRFile(){
    myfile.close();
}

void IRLargestVar(int i){
    
}
// Function for assigning the value of one variable to another variable

void varEqVar(int id1, int id2){
    string tId1 = "T" + to_string(id1 + 1);
    string tId2 = "T" + to_string(id2 + 1);
    myfile << tId1 << " = " << tId2 << "\n";
 
}
// Function to check if a variable is recursive and return the corresponding string

string isRecur(int r){
    if(r == 0){
        return "";
    }
    return "R" + to_string(r);
}
// Function for setting parameter registers in IR code

string setParReg(int i){
    return "a" + to_string(i);
}
// Function for setting general registers in IR code

string setReg(int i){
    if(i >= 9){
        return "s" + to_string(i-9);
    }
    return  "T" + to_string(i+1);
}
// Function for assigning a numeric value to a variable

void varEqNum(int id1, string data){
    myfile << setReg(id1) << " = " << data << "\n";
}
// Function for starting a binary operation in IR code (e.g., +, -, *, /)

void IRBinOpStart(int id1, int id2){
    myfile << "\n" << setReg(id1) << " = " << setReg(id2);
}
// Overloaded function for starting a binary operation with a numeric value

void IRBinOpStart(int id1, string data){
    myfile << "\n" << setReg(id1) << " = " << data;
}

void IRBinOpAdd(string bin, int id1, int id2, int id3){
    myfile << " " << bin << " " << setReg(id1) << "\n";
    myfile << setReg(id2) << " = " << setReg(id3);
}

void IRBinOpAdd(string bin, string data, int id2, int id3){
    myfile << " " << bin << " " << data << "\n";
    myfile << setReg(id2) << " = " << setReg(id3);
}
// Function for completing a binary operation in IR code

void IRBinOpEnd(string bin, int id1, int id2, int id3){
    myfile << " " << bin << " " << setReg(id1) << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n";
}
// Overloaded function for completing a binary operation with a numeric value

void IRBinOpEnd(string bin, string data, int id2, int id3){
    myfile << " " << bin << " " << data << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n\n";
}
// Function for writing a variable to the output in IR code

void IRWrite(int id1){
        myfile << "WRITE " << setReg(id1) << "\n";
}
// Function for writing a string to the output in IR code

void IRWriteString(string data){
        myfile << "!" << data << "\n";
}
// Function for writing a variable (as a string) to the output in IR code

void IRWriteStr(string id1){
        myfile << "WRITE " << id1 << "\n";
}
// Function for returning a value from a function in IR code

void IRReturn(int id1){
        myfile << "RETURN " << setReg(id1) << "\n\n";
}
// Function for writing a newline character to the output in IR code

void IRWriteLn(){
    myfile << "WRITELN\n\n";
}
// Function for starting a new function in IR code

void IRStartFunc(string func){
    myfile << "\n" << func << ":\n";
}
// Function for setting a parameter in IR code

void IRSetParam(int i){
    myfile << setReg(i) << " = " << setParReg(i) << "\n";
}
// Function for making a function call in IR code

void IRJal(string func){
    myfile << "jal " << func << "\n";
}

void IRJalReturn(int a){
    myfile << setReg(a) << " = v0\n";
}

void IRIfEqVar(int id1, int id2, int f, int r){
    myfile << "beq " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfEqNum(int id1, string data, int f, int r){
    myfile << "beq " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrVar(int id1, int id2, int f, int r){
    myfile << "bgt " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrNum(int id1, string data, int f, int r){
    myfile << "bgt " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeVar(int id1, int id2, int f, int r){
    myfile << "blt " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeNum(int id1, string data, int f, int r){
    myfile << "blt " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrEqVar(int id1, int id2, int f, int r){
    myfile << "bge " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfGrEqNum(int id1, string data, int f, int r){
    myfile << "bge " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeEqVar(int id1, int id2, int f, int r){
    myfile << "ble " << setReg(id1) << ", " << setReg(id2) << ", if" << f << isRecur(r) << "\n";
}

void IRIfLeEqNum(int id1, string data, int f, int r){
    myfile << "ble " << setReg(id1) << ", " << data << ", if" << f << isRecur(r) << "\n";
}




void IRIfEndGoto(int f, int r){
    myfile << "b ifEnd" << f << isRecur(r) << "\n";
}

void IRIfDecl(int f, int r){
    myfile << "if" << f << isRecur(r) << ":\n";
}

void IRElseEndGoto(int f, int r){
    cout << "IR: b elseEnd" << f << isRecur(r) << "\n";
    myfile << "b elseEnd" << f << isRecur(r) << "\n";
}

void IRElseEndDecl(int f, int r){
    cout << "IR: elseEnd" << f << isRecur(r) << ":\n";
    myfile << "elseEnd" << f << isRecur(r) << ":\n";
}

void IRIfEndDecl(int f, int r){
    cout << "IR: ifEnd" << f << isRecur(r) << ":\n";
    myfile << "ifEnd" << f << isRecur(r) << ":\n";
}

void IRJalInput(int a, int in){
    myfile << setParReg(a) << " = " << setReg(in) << "\n";
}


void IRWhileStart(int a){
    myfile << "whileStart" << a << ":\n";
}

void IRWhileEnd(int a){
    myfile << "whileEnd" << a << ":\n";
}

void IRWhileStartGoTo(int a){
    myfile << "b whileStart" << a << "\n";
}

void IRWhileEndGoTo(int a){
    myfile << "b whileEnd" << a << "\n";
}

void IRWhileCode(int a){
    myfile << "whileCode" << a << ":\n";
}

void IRWhileEqVar(int id1, int id2, int f){
    myfile << "beq " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f<< "\n";
}

void IRWhileEqNum(int id1, string data, int f){
    myfile << "beq " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileGrVar(int id1, int id2, int f){
    myfile << "bgt " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileGrNum(int id1, string data, int f){
    myfile << "bgt " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileLeVar(int id1, int id2, int f){
    myfile << "blt " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileLeNum(int id1, string data, int f){
    myfile << "blt " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileGrEqVar(int id1, int id2, int f){
    myfile << "bge " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileGrEqNum(int id1, string data, int f){
    myfile << "bge " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}

void IRWhileLeEqVar(int id1, int id2, int f){
    myfile << "ble " << setReg(id1) << ", " << setReg(id2) << ", whileCode" << f << "\n";
}

void IRWhileLeEqNum(int id1, string data, int f){
    myfile << "ble " << setReg(id1) << ", " << data << ", whileCode" << f << "\n";
}


void optimizeIR()
{
    ifstream ifs;

    // Open the Intermediate Representation (IR) file for reading
    ifs.open("IRcode.txt");
    
    // Set the maximum size for each line in the IR code
    const int linesize = 100;

    // Declare variables for line processing
    char line[linesize];
    int linecounter = 50;  // Placeholder value for the number of lines in the IR code
    bool flag[linecounter];  // Array to track specific conditions in each line
    int counter = 0;

    // Declare a 2D array to store the lines of the IR code
    char lines[linecounter][linesize];

    // Declare variables for line manipulation and value conversion
    char remainder1[linesize];
    char remainder2[linesize];
    char newstring[linesize];
    char newvalue[linesize];
    int value1;
    int value2;

    int count;
    char linesave[100];

    // Declare variables for identifying and eliminating variables
    char elimvar[2];

    // Set the maximum size of a numeric value in the IR code
    int maxnumsize = 10;

    // Read lines from the IR file and store them in the lines array
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

    // Reset the counter for further use
    counter = 0;

    // Process lines to eliminate variables if they only occur once
    for (int i = 0; i < linecounter; i++)
    {
        // Check if the fifth character of a line is a digit
        if (isdigit(lines[i][5]))
        {
            elimvar[0] = lines[i][0];
            elimvar[1] = lines[i][1];

            // Copy the remaining characters of the line for later use
            for (int j = 5; j < linesize; j++)
            {
                remainder1[j] = lines[i][j];
            }

            // Check subsequent lines for the same variable and replace them
            for (int j = i + 1; j < linecounter; j++)
            {
                for (int k = 0; k < linesize; k++)
                {
                    if (lines[j][k] == elimvar[0] && lines[j][k + 1] == elimvar[1])
                    {
                        // Shift characters to make space for the new value
                        for (int l = k; l < linesize; l++)
                        {
                            lines[j][l + maxnumsize] = lines[j][l];
                            lines[j][l] = ' ';
                            // Copy the new value into the line
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

    // Flag lines with '+' for further processing
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

    // Process flagged lines with '+' to combine consecutive numeric values
    for (int i = 0; i < linecounter; i++)
    {
        if (flag[i] == flag[i + 1])
        {
            // Check if the 11th character in both lines is a digit
            if (isdigit(lines[i][10]) && isdigit(lines[i + 1][10]))
            {
                // Copy the numeric values for addition
                for (int j = 10; j < linesize; j++)
                {
                    remainder1[j] = lines[i][j];
                    remainder2[j] = lines[i + 1][j];
                }

                // Convert the values to integers and perform addition
                value1 = atoi(remainder1);
                value2 = atoi(remainder2);
                value1 = value1 + value2;

                // Convert the result back to a string
                sprintf(newstring, "%d", value1);

                // Copy the result back to the second line
                for (int j = 10; j < linesize; j++)
                {
                    lines[i + 1][j] = newstring[j];
                }

                // Empty the first line
                for (int j = 0; j < linesize; j++)
                {
                    lines[i][j] = ' ';
                }
            }
        }

        // Reset the flag for the next iteration
        flag[i] = 0;
    }

    // Flag lines with '*' for further processing
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

    // Process flagged lines with '*' to handle multiplication by a constant
    for (int i = 0; i < linecounter; i++)
    {
        if (flag[i] == true)
        {
            // Check if the 11th character is a digit
            if (isdigit(lines[i][10]))
            {
                // Copy the numeric value for multiplication
                for (int j = 10; j < linesize; j++)
                {
                    remainder1[j] = lines[i][j];
                }

                // Convert the value to an integer
                count = atoi(remainder1);

                // Copy the line for later use
                for (int j = 0; j < linesize; j++)
                {
                    linesave[j] = lines[i][j];
                }

                // Check if the count is greater than or equal to the remaining lines
                if (count >= linecounter - i - 1)
                {
                    // Empty the lines from the current position to the end
                    for (int j = i; j < linecounter; j++)
                    {
                        for (int k = 0; k < linesize; k++)
                        {
                            lines[j][k] = ' ';
                        }
                    }

                    // Modify the saved line to indicate addition
                    linesave[10] = '+';

                    // Repeat the saved line for the remaining lines
                    for (int j = i; j < linecounter; j++)
                    {

                    }
                }
            }
        }
    }

    // Reset the counter for further use
    counter = 0;

    // Eliminate redundant variables that only occur once
    for (int i = 0; i < linecounter; i++)
    {
        elimvar[0] = lines[i][0];
        elimvar[1] = lines[i][1];

        // Count occurrences of the variable in the remaining lines
        for (int j = 0; j < linecounter; j++)
        {
            if (lines[i][j] == elimvar[0] && lines[i][j + 1] == elimvar[1])
            {
                counter++;
            }
        }

        // If the variable occurs only once, eliminate it from the line
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

    // Close the input file
    ifs.close();
    
    // Open the IR file for writing
    openIRFile();

    // Write the modified lines back to the IR file
    for (int i = 0; i < linecounter; i++)
    {
        for (int j = 0; j < linesize; j++)
        {
            myfile << lines[i][j];
        }
        myfile << "\n";
    }

    // Close the IR file
    closeIRFile();
}
