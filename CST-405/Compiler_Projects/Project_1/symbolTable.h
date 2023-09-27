/*
TODO

Funtion support - Linked lisk/2D array
local vars 

*/

#pragma once
//Symbol table header
#include <string.h>
#include <string>
using namespace std;

FILE* IRcode;

// This is a very simplistic implementation of a symbol table
// You will use this as reference and build a much more robust one

struct Entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //is it a function or a variable?
	char itemType[8];  // Is it int, char, etc.?
	int arrayLength;
	char scope[50];     // global, or the name of the function
};

struct Entry symTabItems[100];
int symTabIndex = 0;

void symTabAccess(void){
	printf("::::> Symbol table accessed.\n");
}

void addItem(char inName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
	scope = "Global";
	printf("\n Another one: %s\n", scope);
	

		// what about scope? should you add scope to this function?
		symTabItems[symTabIndex].itemID = symTabIndex;
		strcpy(symTabItems[symTabIndex].itemName, inName);
		strcpy(symTabItems[symTabIndex].itemKind, itemKind);
		strcpy(symTabItems[symTabIndex].itemType, itemType);
		symTabItems[symTabIndex].arrayLength = arrayLength;
		strcpy(symTabItems[symTabIndex].scope, scope);
		symTabIndex++;
	
}
/*
Entry* insert(string item) {
	printf("\n WHAT IS THIS: %s\n", item);
  	// insert symbol into the
  	Entry *newEntry = new Entry;
	newEntry->itemName = item;
	return newEntry;
}
*/
void showSymTable(){
	printf("itemID    itemName    itemKind    itemType     ArrayLength    itemSCope\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i=0; i<symTabIndex; i++){
		printf("%5d %15s  %7s  %7s %6d %15s \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope);
	}
	

	printf("-----------------------------------------------------------------------\n");
}

int found(string itemName, char scope[50]){
	// Lookup an identifier in the symbol table
	// what about scope?
	// return TRUE or FALSE
	// Later on, you may want to return additional information
	for(int i=0; i<100; i++){
		int str1 = (symTabItems[i].itemName == itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return 1; // found the ID in the table
		}
	}
	return 0;
}

int findID(char itemName[50], char scope[50]){
	for(int i=0; i<100; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return i; // found the ID in the table
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
	/*
	const char* idType1 = getVariableType(itemName1, scope);
	const char* idType2 = getVariableType(itemName2, scope);

	printf("%s = %s\n", idType1, idType2);

	int typeMatch = strcmp(idType1, idType2);
	if(typeMatch == 0){
		return 1;
	}
	else return 0;
	*/
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

