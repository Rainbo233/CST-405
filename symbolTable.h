// symbol table which gathers the tokens and stores them to determine what each part of the souce code means wether its a identifer, int, char, function, etc
#pragma once

#include <string.h>
#include <string>
using namespace std;

FILE* IRcode;



struct Entry
{
	int itemID;
	char itemName[50];  // identifier
	char itemKind[8];  // function or varible
	char itemType[8];  // see if its a int, char, etc
	int arrayLength;
	char scope[50];    // name of the function
};

struct Entry symTabItems[100];
int symTabIndex = 0;

void symTabAccess(void){
	printf("::::> Symbol table accessed.\n");
}

void addItem(char inName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
	scope = "Global";
	printf("\n Another one: %s\n", scope);
	

		symTabItems[symTabIndex].itemID = symTabIndex;
		strcpy(symTabItems[symTabIndex].itemName, inName);
		strcpy(symTabItems[symTabIndex].itemKind, itemKind);
		strcpy(symTabItems[symTabIndex].itemType, itemType);
		symTabItems[symTabIndex].arrayLength = arrayLength;
		strcpy(symTabItems[symTabIndex].scope, scope);
		symTabIndex++;
	
}

void showSymTable(){
	printf("itemID    itemName    itemKind    itemType     ArrayLength    itemSCope\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i=0; i<symTabIndex; i++){
		printf("%5d %15s  %7s  %7s %6d %15s \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope);
	}
	

	printf("-----------------------------------------------------------------------\n");
}

int found(string itemName, char scope[50]){

	for(int i=0; i<100; i++){
		int str1 = (symTabItems[i].itemName == itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return 1; 
		}
	}
	return 0;
}

int findID(char itemName[50], char scope[50]){
	for(int i=0; i<100; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return i; 
		}
	}
	return -1;
}

int getEmptyID(){
	for(int i=0; i<100; i++){
		int str1 = strcmp(symTabItems[i].itemName, "");
		if(str1 == 0){
			return i;
		}
	}
	return -1;
}

int compareTypes(string itemName1, string itemName2, char scope[50]){
	printf("\n-------------------------");
	printf("\n Compare Types: %s %s %s \n", itemName1, itemName2, scope);

}

string cBS(char* a)
{
	int size = sizeof(a);
	printf("++:%d\n", size);
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
		printf("+++:%s\n", a[i]);
        s = s + a[i];
    }
    return s;
}

