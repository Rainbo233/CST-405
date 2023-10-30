// ir code file to generate the ir source code to Ircode.txt



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
 
}

string setParReg(int i){
    return "a" + to_string(i);
}

string setReg(int i){
    if(i > 8){
        return "s" + to_string(i-7);
    }
    return  "T" + to_string(i+1);
}

void varEqNum(int id1, string data){
    myfile << setReg(id1) << " = " << data << "\n";
}

void IRBinOpStart(int id1, int id2){
    myfile << "\n" << setReg(id1) << " = " << setReg(id2);
}

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

void IRBinOpEnd(string bin, int id1, int id2, int id3){
    myfile << " " << bin << " " << setReg(id1) << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n";
}

void IRBinOpEnd(string bin, string data, int id2, int id3){
    myfile << " " << bin << " " << data << "\n";
    myfile << setReg(id2) << " = " << setReg(id3) << "\n\n";
}

void IRWrite(int id1){
        myfile << "WRITE " << setReg(id1) << "\n";
}

void IRReturn(int id1){
        myfile << "RETURN " << setReg(id1) << "\n\n";
}

void IRWriteLn(){
    myfile << "WRITELN\n\n";
}

void IRStartFunc(string func){
    myfile << "\n" << func << ":\n";
}

void IRSetParam(int i){
    myfile << setReg(i) << " = " << setParReg(i) << "\n";
}

void IRJal(string func){
    myfile << "jal " << func << "\n";
}

void IRJalReturn(int a){
    myfile << setReg(a) << " = v0\n";
}

void IRJalInput(int a, int in){
    myfile << setParReg(a) << " = " << setReg(in) << "\n";
}

void optimizeIR()
{
    ifstream ifs;

    ifs.open("IRcode.txt");
    
    

    const int linesize = 100;
    char line[linesize];
    int linecounter = 50; 
    bool flag[linecounter];
    int counter = 0;
    
   

    char lines[linecounter][linesize];

   
    char remainder1[linesize];
    char remainder2[linesize];
    char newstring[linesize];
    char newvalue[linesize];
    int value1;
    int value2;


    int count;
    char linesave[100];


    char elimvar[2];

  
    int maxnumsize = 10;
    

   
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
                        
                            lines[j][k] = ' ';
                        }
                    }

                 
                    linesave[10] = '+';

                   
                    for (int j = i; j < linecounter; j++)
                    {

                    }

                }
            }
        }


    }


   
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
