/*
Semantic
ToDO
update to new grammer

Optizer
ToDo
bump to IR code gen, not post gen
Add at least 1 more optizer
update to new grammer

*/


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "ctype.h"
using namespace std;

ofstream myfile;

void openIRFile(){
    myfile.open ("IRcode.txt");
}

void closeIRFile(){
    myfile.close();
}

void varEqVar(int id1, int id2){
    string tId1 = "T" + to_string(id1 + 1);
    string tId2 = "T" + to_string(id2 + 1);

    myfile << tId1 << " = " << tId2 << "\n";
    /*
    myfile << tId1 << " = " << data1 << "\n";
    myfile << tId2 << " = " << data2 << "\n";
    myfile << tId2 << " = " << tId1 << "\n";
    
    //fprintf(IRcode, "%s = %s\n", tId1, data1);
    //fprintf(IRcode, "%s = %s\n", tId2, data2);
    //fprintf(IRcode, "%s = %s\n", tId2, tId1);
    */
}

void varEqNum(int id1, string data){
    string tId1 = "T" + to_string(id1 + 1);
    myfile << tId1 << " = " << data << "\n";
}

void IRBinOpStart(int id1, int id2){
    string tId1 = "T" + to_string(id1 + 1);
    string tId2 = "T" + to_string(id2 + 1);
    myfile << "\n" << tId1 << " = " << tId2;
}

void IRBinOpStart(int id1, string data){
    string tId1 = "T" + to_string(id1 + 1);
    myfile << "\n" << tId1 << " = " << data;
}

void IRBinOpAdd(string bin, int id1, int id2, int id3){
    string tId1 = "T" + to_string(id1 + 1);
    string tId2 = "T" + to_string(id2 + 1);
    string tId3 = "T" + to_string(id3 + 1);
    myfile << " " << bin << " " << tId1 << "\n";
    myfile << tId2 << " = " << tId3;
}

void IRBinOpAdd(string bin, string data, int id2, int id3){
    string tId2 = "T" + to_string(id2 + 1);
    string tId3 = "T" + to_string(id3 + 1);
    myfile << " " << bin << " " << data << "\n";
    myfile << tId2 << " = " << tId3;
}

void IRBinOpEnd(string bin, int id1, int id2, int id3){
    string tId1 = "T" + to_string(id1 + 1);
    string tId2 = "T" + to_string(id2 + 1);
    string tId3 = "T" + to_string(id3 + 1);
    myfile << " " << bin << " " << tId1 << "\n";
    myfile << tId2 << " = " << tId3 << "\n";
}

void IRBinOpEnd(string bin, string data, int id2, int id3){
    string tId2 = "T" + to_string(id2 + 1);
    string tId3 = "T" + to_string(id3 + 1);
    myfile << " " << bin << " " << data << "\n";
    myfile << tId2 << " = " << tId3 << "\n\n";
}

void IRWrite(int id1){
        string tId1 = "T" + to_string(id1 + 1);
        myfile << "WRITE " << tId1 << "\n";
}

void optimizeIR()
{
    ifstream ifs;

    ifs.open("IRcode.ir");
    
    

    // Variables for line construction
    const int linesize = 100;
    char line[linesize];
    int linecounter = 50; // For furture dynamic allocation
    bool flag[linecounter];
    int counter = 0;
    
    //2D Array to store all lines

    char lines[linecounter][linesize];

    // For constant folding
    char remainder1[linesize];
    char remainder2[linesize];
    char newstring[linesize];
    char newvalue[linesize];
    int value1;
    int value2;

    //// For strength reduction
    //int count;
    //char linesave[100];

    // For dead code elim
    char elimvar[2];

    // For constant prop
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

    // Constant propogation
    counter = 0;
    for (int i = 0; i < linecounter; i++)
    {
        // Find if a function declaration is set to an integer
        if (isdigit(lines[i][5]))
        {
            // Integer found
            elimvar[0] = lines[i][0];
            elimvar[1] = lines[i][1];
            
            // Replace all future instances with integer
            // Since integers can have more than 1 character, we have to transfer all characters over
            for (int j = 5; j < linesize; j++)
            {
                remainder1[j] = lines[i][j];
            }

            //Find instance of usage of this variable after first one
            for (int j = i+1; j < linecounter; j++)
            {
                for (int k = 0; k < linesize; k++)
                {
                    if(lines[j][k] == elimvar[0] && lines[j][k+1] == elimvar[1])
                    {
                        // Bump all variables out
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
    // Nested to mark which lines have + signs
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
    
    // Combine lines
    for (int i = 0; i < linecounter; i++)
    {
       
        // Current line and next line both have a + 
        if (flag[i] == flag[i + 1])
        {
            

            // Check if both lines have a constant
            if (isdigit(lines[i][10]) && isdigit(lines[i + 1][10]))
            {
                // Since integers can have more than 1 character, we have to transfer all characters over
                for (int j = 10; j < linesize; j++)
                {
                    remainder1[j] = lines[i][j];
                    remainder2[j] = lines[i + 1][j];
                }
                // Convert cstrings to int
                value1 = atoi(remainder1);
                value2 = atoi(remainder2);

                //Store the sum
                value1 = value1 + value2;

                // Convert back to string
                sprintf(newstring, "%d", value1);

                // Put the number back in the line
                for (int j = 10; j < linesize; j++)
                {
                    lines[i + 1][j] = newstring[j];
                }

                // Replace the first entry with spaces
                for (int j = 0; j < linesize; j++)
                {
                    lines[i][j] = ' ';
                }
            }
        }
        
        // Set current line to false 
        flag[i] = 0;
    }

    // Strength reduction
    // Since we have the framework implemented to allow for multiplication, we can perform strength reduction on it (currently incomplete due to time constraints)
    // Nested loop to mark which lines have * signs
    //for (int i = 0; i < linecounter; i++)
    //{
    //    for (int j = 0; i < linesize; i++)
    //    {
    //        if (lines[i][j] == '*')
    //        {
    //            flag[i] = true;
    //        }
    //    }
    //}

    //// Loop to split up the equation into more lines
    //for (int i = 0; i < linecounter; i++)
    //{
    //    if (flag[i] == true)
    //    {
    //        
    //        // Check if line has a constant
    //        if (isdigit(lines[i][10]))
    //        {
    //            // Since integers can have more than 1 character, we have to transfer all characters over
    //            for (int j = 10; j < linesize; j++)
    //            {
    //                remainder1[j] = lines[i][j];
    //            }
    //            // Convert cstrings to int
    //            count = atoi(remainder1);

    //            // Save line that's getting broken up
    //            for (int j = 0; j < linesize; j++)
    //            {
    //                linesave[j] = lines[i][j];
    //            }

    //            // Check if split is too large
    //            if (count >= linecounter - i - 1)
    //            {
    //                remainder1 = count - (linecounter + i) - 1;
    //                
    //                // Bump all array values out
    //                for (int j = i; j < linecounter; j++)
    //                {
    //                    for (int k = 0; k < linesize; k++)
    //                    {
    //                        lines[j + remainder1][k] = lines[j][k];
    //                        
    //                        // Delete current line
    //                        lines[j][k] = ' ';
    //                    }
    //                }

    //                // Change linesave to have a +
    //                linesave[10] = '+';

    //                // Copy and paste linesave for all remaining lines except the last one
    //                for (int j = i; j < linecounter; j++)
    //                {

    //                }

    //            }
    //        }
    //    }


    //}


    // 


    // Dead code elimination
    // Search through list of lines for a var declaration
    counter = 0;
    for (int i = 0; i < linecounter; i++)
    {
        // Set our variable to check to the first two characters of the line (the variable declaration)
        elimvar[0] = lines[i][0];
        elimvar[1] = lines[i][1];

        // Search for instances of line
        for (int j = 0; j < linecounter; j++)
        {
            if (lines[i][j] == elimvar[0] && lines[i][j+1] == elimvar[1])
            {
                // instance found
                counter++;
            }
        }

        if (counter > 1)
        {
            // Not dead code (used more than once)
            counter = 0;
        }
        else if (counter == 1)
        {
            // Code only appears once 
            // Empty the line
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
