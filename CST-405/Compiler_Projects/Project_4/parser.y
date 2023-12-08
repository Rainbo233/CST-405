%{
// Header section including necessary libraries and external declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <sys/time.h>

#include "SymbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "CodeGen.h"
#include "Semantic.h"

BinTree AST;  // Declaration of an Abstract Syntax Tree object

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* IRfile;

void yyerror(const char* s);
char currentScope[50];
int semanticCheckPassed;
%}

%union {
    int number;
    char character;
    char* string;
    struct Node* ast;
    struct Entry *symbol;
    int i;
}

// Tokens and their types
%token <string> CHAR INT
%token <string> ID STRING
%token <char> SEMICOLON
%token <char> EQ
%token <number> NUMBER
%token WRITE READ WRITELN RETURN
%token IF ELSE WHILE
%token LPAR LBRA RCBRA LCBRA COMMA
%left PLUS MINUS
%left MULT DIV
%left RPAR RBRA
%left UNARY
%left LESSTHN GRTRTHN LESSTHNEQ GRTRTHNEQ EQEQ NOTEQ
%right EQ

// Printers for custom printing of tokens
%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

%type <string> Type
%type <ast> Program DeclList Decl VarDecl Stmt StmtList Expr ParamDeclList ParamDecl Block BlockList FuncDeclList FuncDecl FuncID Primary ExprList Condition IfBlock WhileBlock BlockListEmpty

%start Program

%%

// Grammar rules and actions start here

Program: FuncDeclList   {AST.addNode("Program",$1,NULL); printf("\n PARSER START? \n");}
       | Program FuncDeclList {AST.addNode("Program",$1,$2);}
;

// Function declaration list
FuncDeclList: FuncDecl              {$$ = $1;}
            | FuncDecl FuncDeclList {$$ = AST.addNode("FuncDeclList",$1,$2);}
;

// Function declaration
FuncDecl : Type ID LPAR ParamDeclList RPAR Block {
    printf("\n FUNCDECL \n");
    $$ = AST.addNode("Func",AST.addNode($2, NULL, NULL),AST.addNode("FuncInfo",$4,$6));
    cout << "SCOPE::" << cBS($2) << "\n";
    cout << "TEMP\n";
    showTempSymTable();
    cout << "\n SCOPE TABLE \n";
    moveTable();
    showAllSymTable();
    cout << "\n ADD NEW SCOPE \n";
    addFunc($2, $1);
    showFuncTable();
}
;

// Parameter declaration list
ParamDeclList: %empty                {$$ = NULL;}
            | ParamDecl             {$$ = $1;}
            | ParamDecl COMMA ParamDeclList {$$ = AST.addNode("ParamDeclList",$1,$3);}
;

// Logical operations
LogicOp: LESSTHN 
        | GRTRTHN
        | LESSTHNEQ
        | GRTRTHNEQ
        | EQEQ
        | NOTEQ
;

// Block of code
Block: LCBRA BlockList RCBRA {$$ = $2;}
;

// Condition for if statements
Condition: Expr LESSTHN Expr {$$ = AST.addNode("<",$1,$3);}
        | Expr GRTRTHN Expr {$$ = AST.addNode(">",$1,$3);}
        | Expr LESSTHNEQ Expr {$$ = AST.addNode("<=",$1,$3);}
        | Expr GRTRTHNEQ Expr {$$ = AST.addNode(">=",$1,$3);}
        | Expr EQEQ Expr {$$ = AST.addNode("==",$1,$3);}
        | Expr NOTEQ Expr {$$ = AST.addNode("!=",$1,$3);}
;

// List of blocks
BlockList: BlockList StmtList        {$$ = AST.addNode("BlockList",$1,$2);}
        | BlockListEmpty StmtList    {$$ = AST.addNode("BlockList",$2,$1);}
        | BlockList VarDecl          {$$ = AST.addNode("BlockList",$1,$2);}
        | BlockListEmpty VarDecl     {$$ = AST.addNode("BlockList",$1,$2);}
;

// Empty block list
BlockListEmpty: %empty                    {$$ = AST.addNode("BlockEnd",NULL,NULL);}
;

// Parameter declaration
ParamDecl: Type ID                     {
    printf("\n ParamDecl \n");
    $$ = AST.addNode($2, NULL, NULL);
    addParam($2, $1, 1);
    showSymTable();
}
    | Type ID LBRA NUMBER RBRA {$$ = AST.addNode($2, NULL, NULL);
                                for (int x = 0; x < $4; x++){
                                    string n = cBS($2) + "[" + to_string(x) + "]";
                                    cout << "Array: " << n <<"\n";
                                    addParam((char*)n.c_str(),$1,1);
                                }
                                showSymTable();
    }
;

// Declaration list
DeclList:   Decl DeclList   {$$ = AST.addNode("DeclList",$1,$2);}
        | Decl              { $$ = $1; }
        | %empty            {$$ = NULL;}
;

// Declaration
Decl:   VarDecl { $$ = $1;}
    | StmtList {$$ = $1;}
    | Decl VarDecl {$$ = AST.addNode("Decl",$1,$2);}
    | Decl StmtList {$$ = AST.addNode("Decl",$1,$2);}
;

// Variable declaration
VarDecl: Type ID SEMICOLON { printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
                                symTabAccess();
                                int inSymTab = found($2, 0);

                                if (inSymTab == 1) {
                                    addItem($2, "Var", $1,0, currentScope);
                                    printf("\n Item Name: %s\n", $2);
                                }else
                                    printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
                                showSymTable();

                                $$ = AST.addNode($2,NULL, NULL);
                                printf("----------> %s", $$->Left);
                            }
    | Type ID LBRA NUMBER RBRA SEMICOLON {
                                printf("\n ARRAY NUMBER %d\n", $4);
                                printf("INPUT: %s\n", $2);
                                for (int x = 0; x < $4; x++){
                                    string n = cBS($2) + "[" + to_string(x) + "]";
                                    cout << "Array: " << n <<"\n";
                                    addItem((char*)n.c_str(), "Var", $1,0, currentScope);
                                }
                                showSymTable();
                                $$ = AST.addNode($2,NULL, NULL);
                            }
;

// Data type
Type: INT  {$$ = $1;}
    | CHAR {$$ = $1;}
;

// Function identifier
FuncID: ID LPAR {$$ = $1; printf("\n FUNCTION ID\n")}
;

// List of statements
StmtList:   Stmt          {$$ = $1;}
        | Stmt StmtList {$$ = AST.addNode("StmtList",$1,$2);}
;

// Statements
Stmt:   SEMICOLON   {}
    | Primary EQ Expr SEMICOLON    { printf("\n RECOGNIZED RULE: prime=Expr statement\n"); 
                    cout << "\n\nEquals\n" << $3 << "\n";
                
                    $$ = AST.addNode("=",$1,$3);

                    if(found($3->data, 0) != 1){
                        printf("Semantic error: Variable %s has not been declared in scope %s \n", $3, currentScope);
                        semanticCheckPassed = 0;
                    }

                    printf("\nChecking types: \n");
                }
    | WRITE Expr SEMICOLON{$$ = AST.addNode("WRITE",$2,$2);}
    | WRITE STRING SEMICOLON{$$ = AST.addNode("WRITE",AST.addNode($2,NULL,NULL),AST.addNode($2,NULL,NULL));}
    | RETURN Expr SEMICOLON{$$ = AST.addNode("RETURN",$2,NULL);}
    | WRITELN SEMICOLON {$$ = AST.addNode("WRITELN",NULL,NULL);}
    | IF LPAR Condition RPAR IfBlock {$$ = AST.addNode("IF", $3, $5);}
    | WHILE LPAR Condition RPAR WhileBlock {$$ = AST.addNode("WHILE", $3, $5);}
;

// Expression
Expr:   Primary         {$$ = $1; cout << "prine->expr\n";}
    | ID {$$ = AST.addNode($1, NULL, NULL); printf("\n RECOGNIZED RULE: Simplest expression: %s \n", $1); }
    | Expr MULT Expr    {printf("\n RECOGNIZED RULE: Expr*Expr statement\n");
                $$ = AST.addNode("*",$3,$1);
                }
    | Expr MULT Primary {printf("\n RECOGNIZED RULE: Expr*Prime statement\n");
                $$ = AST.addNode("*",$1,$3);
                }
    | Expr PLUS Expr    {printf("\n RECOGNIZED RULE: MULT statement\n");
                cout << "\n\nPLUS\n";
                $$ = AST.addNode("+",$3,$1);
                }
    | Primary PLUS Expr {printf("\n RECOGNIZED RULE: MULT statement\n");
                $$ = AST.addNode("+",$3,$1);
                }   
    | Primary PLUS Primary {printf("\n RECOGNIZED RULE: MULT statement\n");
                $$ = AST.addNode("+",$1,$3);
                }   
    | Primary DIV Expr  {printf("\n RECOGNIZED RULE: DIV statement\n");
                $$ = AST.addNode("/",$3,$1);
                }   
    | Primary DIV Primary {printf("\n RECOGNIZED RULE: DIV statement\n");
                $$ = AST.addNode("/",$1,$3);
                }   
    | Primary MINUS Expr    {printf("\n RECOGNIZED RULE: MINUS statement\n");
                $$ = AST.addNode("-",$3,$1);
                }   
    | Primary MINUS Primary {printf("\n RECOGNIZED RULE: MINUS statement\n");
                $$ = AST.addNode("-",$1,$3);
                }       
;

// If block
IfBlock: Block {$$ = AST.addNode("Block", $1,NULL);}
        | Block ELSE Block {printf("\nELSE\n");
            $$ = AST.addNode("Block", $1,AST.addNode("ELSE",AST.addNode("Block",$3,NULL),NULL));}
;

// While block
WhileBlock: Block {$$ = AST.addNode("Block", $1,AST.addNode("WhileEnd", NULL,NULL));}
;

// Primary expression
Primary: ID                     {$$ = AST.addNode($1, NULL, NULL);
                                printf("\nPrimary BS \n");
                                }
    | NUMBER PLUS NUMBER                {$$ = AST.addNum($1 + $3);}
    | NUMBER PLUS NUMBER                {$$ = AST.addNum($1 - $3);}
    | NUMBER                {$$ = AST.addNum($1);}
    | MINUS NUMBER                {$$ = AST.addNum($2 * -1);}
    | ID LPAR ExprList RPAR        {$$ = AST.addNode("FuncCall",AST.addNode($1, NULL, NULL),$3);
                                
                                }
    | ID LBRA NUMBER RBRA   {
                                cout << ">> ID[]\n";
                                string idArray = cBS($1) + "[" + to_string($3) + "]";
                                $$ = AST.addNode(idArray, NULL, NULL);
                                }
;

// Expression list
ExprList: %empty                {$$ = NULL;}
            | Expr                {$$ = $1;}
            | Expr COMMA ExprList {$$ = AST.addNode("ExprList",$1,$3);}
;
%%

// Main function
int main(int argc, char**argv)
{
    // Timing the compilation
    auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    printf("\n\n##### COMPILER STARTED #####\n\n");

    // Checking if an input file is provided
    if (argc > 1){
        if(!(yyin = fopen(argv[1], "r")))
        {
            perror(argv[1]);
            return(1);
        }
    }
    yyparse();
    AST.printTree(AST.root,0);
    AST.optimizeTree(AST.root);
    AST.printTree(AST.root,0);
    openIRFile();
    AST.genIR(AST.root);
    closeIRFile();
    openASMFile();
    ASMGen();
    closeASMFile();
    cout << "Time for compilation: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - millisec << " Milliseconds\n";
}

// Error handling function for yacc
void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
