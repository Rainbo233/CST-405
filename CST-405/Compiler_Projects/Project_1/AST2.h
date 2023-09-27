//Abstract Syntax Tree Implementation
#include <string.h>

struct AST{
	char nodeType[50];
	char LHS[50];
	char RHS[50];
	
	struct AST * left;
	struct AST * right;
	// review pointers to structs in C 
	// complete the tree struct with pointers
};



struct AST * AST_assignment(char nodeType[50], char LHS[50], char RHS[50]){
	

	struct AST* ASTassign = malloc(sizeof(struct AST));
	strcpy(ASTassign->nodeType, nodeType);
	strcpy(ASTassign->LHS, LHS);
	strcpy(ASTassign->RHS, RHS);
	

/*
       =
	 /   \
	x     y

*/	printf("\n What is this:%s \n", ASTassign);
	return ASTassign;
	
}
struct AST * AST_BinaryExpression(char nodeType[50], char LHS[50], char RHS[50]){

	struct AST* ASTBinExp = malloc(sizeof(struct AST));
	strcpy(ASTBinExp->nodeType, nodeType);
	strcpy(ASTBinExp->LHS, LHS);
	strcpy(ASTBinExp->RHS, RHS);
	return ASTBinExp;
	
}
struct AST * AST_Type(char nodeType[50], char LHS[50], char RHS[50]){

	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
		
	return ASTtype;
	
}

struct AST * AST_Func(char nodeType[50], char LHS[50], char RHS[50]){
	
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
		
	return ASTtype;
	
}

struct AST * AST_Write(char nodeType[50], char LHS[50], char RHS[50]){
	
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
		
	return ASTtype;
	
}

void printTree(struct AST* thisNode, int indent){
  if (thisNode != NULL)
    for(int i = 0; i < indent; i++) {printf("|     ");}
  else
    return;
  	printf("|-----%s\n",thisNode->nodeType);
	printTree(thisNode->LHS,indent + 1);  //recursive call
	printTree(thisNode->RHS,indent + 1); //recursive call
}
























