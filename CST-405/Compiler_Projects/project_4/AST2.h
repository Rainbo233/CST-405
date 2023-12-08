#include <string.h>

// Define a struct for Abstract Syntax Tree (AST)
struct AST {
    char nodeType[50];
    char LHS[50];
    char RHS[50];
    struct AST *left;
    struct AST *right;
};

// Function to create an AST node for assignment operation
struct AST *AST_assignment(char nodeType[50], char LHS[50], char RHS[50]) {
    // Allocate memory for the new AST node
    struct AST *ASTassign = malloc(sizeof(struct AST));
    
    // Copy values to the new node
    strcpy(ASTassign->nodeType, nodeType);
    strcpy(ASTassign->LHS, LHS);
    strcpy(ASTassign->RHS, RHS);

    // Return the newly created AST node
    return ASTassign;
}

// Function to create an AST node for binary expression
struct AST *AST_BinaryExpression(char nodeType[50], char LHS[50], char RHS[50]) {
    // Allocate memory for the new AST node
    struct AST *ASTBinExp = malloc(sizeof(struct AST));
    
    // Copy values to the new node
    strcpy(ASTBinExp->nodeType, nodeType);
    strcpy(ASTBinExp->LHS, LHS);
    strcpy(ASTBinExp->RHS, RHS);

    // Return the newly created AST node
    return ASTBinExp;
}

// Function to create an AST node for type information
struct AST *AST_Type(char nodeType[50], char LHS[50], char RHS[50]) {
    // Allocate memory for the new AST node
    struct AST *ASTtype = malloc(sizeof(struct AST));
    
    // Copy values to the new node
    strcpy(ASTtype->nodeType, nodeType);
    strcpy(ASTtype->LHS, LHS);
    strcpy(ASTtype->RHS, RHS);

    // Return the newly created AST node
    return ASTtype;
}

// Function to create an AST node for function
struct AST *AST_Func(char nodeType[50], char LHS[50], char RHS[50]) {
    // Allocate memory for the new AST node
    struct AST *ASTfunc = malloc(sizeof(struct AST));
    
    // Copy values to the new node
    strcpy(ASTfunc->nodeType, nodeType);
    strcpy(ASTfunc->LHS, LHS);
    strcpy(ASTfunc->RHS, RHS);

    // Return the newly created AST node
    return ASTfunc;
}

// Function to create an AST node for write operation
struct AST *AST_Write(char nodeType[50], char LHS[50], char RHS[50]) {
    // Allocate memory for the new AST node
    struct AST *ASTwrite = malloc(sizeof(struct AST));
    
    // Copy values to the new node
    strcpy(ASTwrite->nodeType, nodeType);
    strcpy(ASTwrite->LHS, LHS);
    strcpy(ASTwrite->RHS, RHS);

    // Return the newly created AST node
    return ASTwrite;
}

// Function to print the AST tree recursively
void printTree(struct AST *thisNode, int indent) {
    if (thisNode != NULL) {
        // Print indentation for better visualization
        for (int i = 0; i < indent; i++) {
            printf("|     ");
        }

        // Print the current node's type
        printf("|-----%s\n", thisNode->nodeType);

        // Recursively print the left and right subtrees
        printTree(thisNode->left, indent + 1);
        printTree(thisNode->right, indent + 1);
    } else {
        // If the node is NULL, return
        return;
    }
}
