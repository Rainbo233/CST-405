// The following code defines and implements a simple symbol table and related functions.
// The symbol table is used to store information about variables, functions, and parameters.

#pragma once
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include "semantic.h"
using namespace std;

// Define the structure for an entry in the symbol table
struct Entry
{
    int itemID;
    char itemName[50];
    char itemKind[8];
    char itemType[8];
    int arrayLength;
    char scope[50];
    int isParam = 0;
};

// Global symbol table arrays and indices
struct Entry symTabItems[100];
int symTabIndex = 0;

struct Entry tempSymTable[100];
int tempSymIndex = 0;

struct Entry functSymTable[100];
int functSymIndex = 0;

struct Entry symTable[100][100];
int symIndex = 0;

// Function to access the symbol table
void symTabAccess(void)
{
    printf("::::> Symbol table accessed.\n");
}

// Function to add an item to the temporary symbol table
void addItem(char inName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50])
{
    scope = "TempScope"; // This line may not be intended to modify the input parameter.
    printf("\n Another one: %s\n", scope);

    tempSymTable[tempSymIndex].itemID = symTabIndex;
    strcpy(tempSymTable[tempSymIndex].itemName, inName);
    strcpy(tempSymTable[tempSymIndex].itemKind, itemKind);
    strcpy(tempSymTable[tempSymIndex].itemType, itemType);
    tempSymTable[tempSymIndex].arrayLength = arrayLength;
    strcpy(tempSymTable[tempSymIndex].scope, scope);
    tempSymIndex++;
}

// Function to add a parameter to the temporary symbol table
void addParam(char inName[50], char itemType[8], int par)
{
    cout << "Adding param\n";
    strcpy(tempSymTable[tempSymIndex].itemName, inName);
    strcpy(tempSymTable[tempSymIndex].itemType, itemType);
    tempSymTable[tempSymIndex].isParam = par;
    tempSymIndex++;
}

// Function to add a function to the function symbol table
void addFunc(char inName[50], char itemType[8])
{
    strcpy(functSymTable[functSymIndex].itemName, inName);
    strcpy(functSymTable[functSymIndex].itemType, itemType);
    functSymIndex++;
}

// Function to get the scope of a function from the function symbol table
int getScope(string n)
{
    for (int i = 0; i < functSymIndex; i++)
    {
        if (cBS(functSymTable[i].itemName) == n)
        {
            return i;
        }
    }
    cout << "\n\nNO SCOPE FOUND FOR " << n << "!\n\n";
    return 0;
}

// Function to display the temporary symbol table
void showTempSymTable()
{
    printf("itemName    itemType    Param\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < tempSymIndex; i++)
    {
        printf("%5s %9s %9d\n", tempSymTable[i].itemName, tempSymTable[i].itemType, tempSymTable[i].isParam);
    }
    printf("-----------------------------------------------------------------------\n");
}

// Function to display all entries in the symbol table
void showAllSymTable()
{
    for (int i = 0; i < symIndex; i++)
    {
        printf("itemName    itemType     Param\n");
        printf("-----------------------------------------------------------------------\n");

        for (int j = 0; j < 100; j++)
        {
            if (cBS(symTable[i][j].itemName) == "")
            {
                break;
            }
            printf("%5s %9s %9d\n", symTable[i][j].itemName, symTable[i][j].itemType, symTable[i][j].isParam);
        }
        printf("-----------------------------------------------------------------------\n");
    }
}

// Function to display the function symbol table
void showFuncTable()
{
    printf("FuncName     itemType\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < functSymIndex; i++)
    {
        printf("%5s %9s\n", functSymTable[i].itemName, functSymTable[i].itemType);
    }
    printf("-------------------------------------------------\n");
}

// Function to display the main symbol table
void showSymTable()
{
    printf("itemID    itemName    itemKind    itemType     ArrayLength    itemSCope\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < symTabIndex; i++)
    {
        printf("%5d %15s  %7s  %7s %6d %15s \n", symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope);
    }
    printf("-----------------------------------------------------------------------\n");
}

// Function to clear the temporary symbol table
void clearTable()
{
    for (int i = 0; i < tempSymIndex; i++)
    {
        strcpy(tempSymTable[i].itemName, "NULL");
        strcpy(tempSymTable[i].itemType, "NULL");
        tempSymTable[i].isParam = 0;
    }
    tempSymIndex = 0;
}

// Function to move entries from the temporary symbol table to the main symbol table
void moveTable()
{
    for (int i = 0; i < tempSymIndex; i++)
    {
        strcpy(symTable[symIndex][i].itemName, tempSymTable[i].itemName);
        strcpy(symTable[symIndex][i].itemType, tempSymTable[i].itemType);
        symTable[symIndex][i].isParam = tempSymTable[i].isParam;
    }
    symIndex++;
    clearTable();
}

// Function to check if an item with a given name is found in the symbol table at a specific scope
int found(string itemName, int scope)
{
    for (int i = 0; i < 100; i++)
    {
        int str1 = (symTable[scope][i].itemName == itemName);
        if (str1 == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Function to find the ID of an item with a given name and scope
int findID(char itemName[50], int scope)
{
    int c = 0;
    for (int i = 0; i < scope; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (cBS(symTable[i][j].itemName) == "")
            {
                break;
            }
            c++;
        }
    }
    for (int i = 0; i < 100; i++)
    {
        int str1 = strcmp(symTable[scope][i].itemName, itemName);
        if (str1 == 0)
        {
            return i + c;
        }
    }
    return -1;
}

// Function to get the ID of an item at a specific index and scope
int getID(int i, int scope)
{
    int c = 0;
    for (int i = 0; i < scope; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (cBS(symTable[i][j].itemName) == "")
            {
                break;
            }
            c++;
        }
    }
    return i + c;
}

// Function to get the index of an empty entry in the symbol table
int getEmptyID()
{
    int c = 0;
    for (int i = 0; i < symIndex; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int str1 = strcmp(symTable[i][j].itemName, "");
            c++;
            if (str1 == 0)
            {
                break;
            }
        }
    }
    return c;
}

// Function to get the number of parameters in a specific scope
int getParamNum(int scope)
{
    for (int i = 0; i < 100; i++)
    {
        if (symTable[scope][i].isParam == 0)
        {
            return i;
        }
    }
    return 0;
}

// Function to compare the types of two items
int compareTypes(string itemName1, string itemName2, char scope[50])
{
    printf("\n-------------------------");
    printf("\n Compare Types: %s %s %s \n", itemName1, itemName2, scope);
}

// End of the provided code.
