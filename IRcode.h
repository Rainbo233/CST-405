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
