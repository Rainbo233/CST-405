// symbol table which gathers the tokens and stores them to determine what each part of the souce code means wether its a identifer, int, char, function, etc

#pragma once
//Symbol table header
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Semantic.h"
using namespace std;

FILE* IRcode;


struct Entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //function or variable?
	char itemType[8];  // Is it int char
	int arrayLength;
	char scope[50];     // the function
	int isParam = 0;
};

struct Entry symTabItems[100];
int symTabIndex = 0;

struct Entry tempSymTable[100]; 
int tempSymIndex = 0;

struct Entry functSymTable[100];
int functSymIndex = 0;

struct Entry symTable[100][100];
int symIndex = 0;

void symTabAccess(void){
	printf("::::> Symbol table accessed.\n");
}

void addItem(char inName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
	scope = "TempScope";
	printf("\n Another one: %s\n", scope);
	

		tempSymTable[tempSymIndex].itemID = symTabIndex;
		strcpy(tempSymTable[tempSymIndex].itemName, inName);
		strcpy(tempSymTable[tempSymIndex].itemKind, itemKind);
		strcpy(tempSymTable[tempSymIndex].itemType, itemType);
		tempSymTable[tempSymIndex].arrayLength = arrayLength;
		strcpy(tempSymTable[tempSymIndex].scope, scope);
		tempSymIndex++;
	
}

void addParam(char inName[50], char itemType[8], int par){
	cout << "Adding param\n";
	strcpy(tempSymTable[tempSymIndex].itemName, inName);
	strcpy(tempSymTable[tempSymIndex].itemType, itemType);
	tempSymTable[tempSymIndex].isParam = par;
	tempSymIndex++;
}

void addFunc(char inName[50], char itemType[8]){
	strcpy(functSymTable[functSymIndex].itemName, inName);
	strcpy(functSymTable[functSymIndex].itemType, itemType);
	functSymIndex++;
}

int getScope(string n){
	for (int i=0; i < functSymIndex; i++){
		if(cBS(functSymTable[i].itemName) == n){
			return i;
		}
	}
	cout << "\n\nNO SCOPE FOUND FOR " << n << "!\n\n";
	return 0;
}

void showTempSymTable(){
	printf("itemName    itemType    Param\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i=0; i<tempSymIndex; i++){
		printf("%5s %9s %9d\n", tempSymTable[i].itemName, tempSymTable[i].itemType, tempSymTable[i].isParam);
	}
	printf("-----------------------------------------------------------------------\n");
}

void showAllSymTable(){
	for (int i=0; i <symIndex; i++){
		printf("itemName    itemType     Param\n");
		printf("-----------------------------------------------------------------------\n");

		for (int j=0; j<100; j++){
			if(cBS(symTable[i][j].itemName) == ""){
				break;
			}
			printf("%5s %9s %9d\n", symTable[i][j].itemName, symTable[i][j].itemType, symTable[i][j].isParam);
		}
		printf("-----------------------------------------------------------------------\n");
	}
}

void showFuncTable(){
	printf("FuncName     itemType\n");
	printf("-------------------------------------------------\n");
	for (int i=0; i < functSymIndex; i++){
		printf("%5s %9s\n", functSymTable[i].itemName, functSymTable[i].itemType);
	}
	printf("-------------------------------------------------\n");
}

void showSymTable(){
	printf("itemID    itemName    itemKind    itemType     ArrayLength    itemSCope\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i=0; i<symTabIndex; i++){
		printf("%5d %15s  %7s  %7s %6d %15s \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope);
	}
	printf("-----------------------------------------------------------------------\n");
}

void clearTable(){
	for (int i=0; i<tempSymIndex; i++){
		strcpy(tempSymTable[i].itemName, "NULL");
		strcpy(tempSymTable[i].itemType, "NULL");
		tempSymTable[i].isParam = 0;
	}
	tempSymIndex = 0;
}

void moveTable(){
	for (int i=0; i<tempSymIndex; i++){
		strcpy(symTable[symIndex][i].itemName, tempSymTable[i].itemName);
		strcpy(symTable[symIndex][i].itemType, tempSymTable[i].itemType);
		symTable[symIndex][i].isParam = tempSymTable[i].isParam;
	}
	symIndex++;
	clearTable();
}


int found(string itemName, int scope){

	for(int i=0; i<100; i++){
		int str1 = (symTable[scope][i].itemName == itemName);
		if( str1 == 0){
			return 1; // found the ID in the table
		}
	}
	return 0;
}

int findID(char itemName[50], int scope){
	int c = 0;
	for(int i=0; i<scope; i++){
		for (int j=0; j<100; j++){
			if(cBS(symTable[i][j].itemName) == ""){
				break;
			}
			c++;
		}
	}
	for(int i=0; i<100; i++){
		int str1 = strcmp(symTable[scope][i].itemName, itemName);
		if( str1 == 0){
			return i + c; 
		}
	}
	return -1;
}

int getID(int i, int scope){
	int c = 0;
	for(int i=0; i<scope; i++){
		for (int j=0; j<100; j++){
			if(cBS(symTable[i][j].itemName) == ""){
				break;
			}
			c++;
		}
	}
	return i + c;
}

int getEmptyID(){
	int c = 0;
	for (int i=0; i <symIndex; i++){
		for(int j=0; j<100; j++){
			int str1 = strcmp(symTable[i][j].itemName, "");
			c++;
			if(str1 == 0){
				break;
			}
		}
	}
	return c;
}

int getParamNum(int scope){
	for (int i=0; i<100; i++){
		if(symTable[scope][i].isParam == 0){
			return i;
		}
	}
	return 0;

}

int compareTypes(string itemName1, string itemName2, char scope[50]){
	printf("\n-------------------------");
	printf("\n Compare Types: %s %s %s \n", itemName1, itemName2, scope);

}


