// Parser file that turns tokens into a binary tree


%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "CodeGen.h"
#include "Semantic.h"

BinTree AST;

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* IRfile;

void yyerror(const char* s);
char currentScope[50]; // global or the name of the function
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

%token <string> CHAR INT
%token <string> ID
%token <char> SEMICOLON
%token <char> EQ
%token <number> NUMBER
%token WRITE READ WRITELN RETURN
%token LPAR LBRA RCBRA LCBRA COMMA
%left PLUS MINUS 
%left MULT DIV
%left RPAR RBRA
%left UNARY
%right EQ

%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

%type <string> Type
%type <ast> Program DeclList Decl VarDecl Stmt StmtList Expr ParamDeclList ParamDecl Block BlockList FuncDeclList FuncDecl FuncID Primary ExprList

%start Program

%%

Program: FuncDeclList   {AST.addNode("Program",$1,NULL);
						printf("\n PARSER START? \n");}
       | Program FuncDeclList {AST.addNode("Program",$1,$2);}
;
FuncDeclList: FuncDecl              {$$ = $1;}
            | FuncDecl FuncDeclList {$$ = AST.addNode("FuncDeclList",$1,$2);}
;

FuncDecl : Type ID LPAR ParamDeclList RPAR Block {printf("\n FUNCDECL \n");
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

												//FINISH nodeType
}
;

ParamDeclList: %empty				{$$ = NULL;}
			| ParamDecl				{$$ = $1;}
			| ParamDecl COMMA ParamDeclList {$$ = AST.addNode("ParamDeclList",$1,$3);
											//FINISH nodeType
			}
;

Block: LCBRA BlockList RCBRA {$$ = $2;}
;

BlockList: %empty					{$$ = NULL;}
		| BlockList StmtList		{$$ = AST.addNode("BLockList",$1,$2);
									//FINISH?
									}
		| BlockList VarDecl			{$$ = AST.addNode("BLockList",$1,$2);
									//FINISH?
									}
;

ParamDecl: Type ID					{printf("\n ParamDecl \n");
									$$ = AST.addNode($2, NULL, NULL);
									addParam($2, $1, 1);
									showSymTable();
									//FINISH?
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

DeclList:	Decl DeclList	{$$ = AST.addNode("DeclList",$1,$2);
							  //$$ = $1;
							}
	| Decl	{ $$ = $1; }
	|%empty {$$ = NULL;}
;

Decl:	VarDecl { $$ = $1;}
	| StmtList {$$ = $1;}
	| Decl VarDecl {$$ = AST.addNode("Decl",$1,$2);}
	| Decl StmtList {$$ = AST.addNode("Decl",$1,$2);}
;

VarDecl:	Type ID SEMICOLON	{ printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
									// Symbol Table
									symTabAccess();
									int inSymTab = found($2, 0);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
									
									if (inSymTab == 1) {
										addItem($2, "Var", $1,0, currentScope);
										printf("\n Item Name: %s\n", $2);
									}else
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
									showSymTable();
									
								  // ---- SEMANTIC ACTIONS by PARSER ----
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
								//Add array indicator
								}
;

Type: INT  {$$ = $1;}
    | CHAR {$$ = $1;}
;

FuncID: ID LPAR {$$ = $1; printf("\n FUNCTION ID\n")}
;

StmtList:	Stmt          {$$ = $1;}
	| Stmt StmtList {$$ = AST.addNode("StmtList",$1,$2);}
;

Stmt:	SEMICOLON	{}
	| Primary EQ Expr SEMICOLON 	{ printf("\n RECOGNIZED RULE: prime=Expr statement\n"); 
					cout << "\n\nEquals\n" << $3 << "\n";
					// ---- SEMANTIC ACTIONS by PARSER ----
					  $$ = AST.addNode("=",$1,$3);
					// Semantic ananysic
					/*if(found($1, 0) != 1){
						printf("Semantic error: Variable %s has not been declared in scope %s \n", $1, currentScope);
						semanticCheckPassed = 0;
					}*/

					if(found($3->data, 0) != 1){
						printf("Semantic error: Variable %s has not been declared in scope %s \n", $3, currentScope);
						semanticCheckPassed = 0;
					}

					printf("\nChecking types: \n");
					/*int typeMatch = compareTypes ($1, $3->data, currentScope);
					if (typeMatch == 0){
						printf("Semantic error: Type mismatch for variables %s and %s \n", $1, $3);
						semanticCheckPassed = 0;
					}

					if (semanticCheckPassed == 1){
						printf("\n\n >IR code is emitted!<\n\n");
						//emitAssignment($1,$3->data);
					}
					
					if(testVarDeclaration($1) == 1)
						if(testVarDeclaration($3) == 1)
							if(checkType($1) == checkType($3))
								//emitIRcode(IRfile, IRAssignment($1,$3));
					*/
				}
	| WRITE Expr SEMICOLON{$$ = AST.addNode("WRITE",$2,$2);};
	| RETURN Expr SEMICOLON{$$ = AST.addNode("RETURN",$2,NULL);
							//FINISH node and return type
							}
	| WRITELN SEMICOLON {$$ = AST.addNode("WRITELN",NULL,NULL);
							//FINISH nodeType
							}
;

Expr: Primary 		{$$ = $1;
					cout << "prine->expr\n";
					}
	| ID {$$ = AST.addNode($1, NULL, NULL); printf("\n RECOGNIZED RULE: Simplest expression: %s \n", $1); }
	| Expr MULT Expr	{printf("\n RECOGNIZED RULE: Expr*Expr statement\n");
				$$ = AST.addNode("*",$3,$1);
				}
	| Expr MULT Primary	{printf("\n RECOGNIZED RULE: Expr*Prime statement\n");
				$$ = AST.addNode("*",$1,$3);
				}
	| Expr PLUS Expr	{printf("\n RECOGNIZED RULE: MULT statement\n");
				cout << "\n\nPLUS\n";
				$$ = AST.addNode("+",$3,$1);
				}
	| Primary PLUS Expr	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("+",$1,$3);
				}	
	| Primary PLUS Primary	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("+",$1,$3);
				}	
	| Primary DIV Expr	{printf("\n RECOGNIZED RULE: DIV statement\n");
				$$ = AST.addNode("/",$1,$3);
				}	
	| Primary DIV Primary	{printf("\n RECOGNIZED RULE: DIV statement\n");
				$$ = AST.addNode("/",$1,$3);
				}	
	| Primary MINUS Expr	{printf("\n RECOGNIZED RULE: MINUS statement\n");
				$$ = AST.addNode("-",$1,$3);
				}	
	| Primary MINUS Primary	{printf("\n RECOGNIZED RULE: MINUS statement\n");
				$$ = AST.addNode("-",$1,$3);
				}		
;

Primary: ID						{$$ = AST.addNode($1, NULL, NULL);
								printf("\nPrimary BS \n");
								}
		| NUMBER				{$$ = AST.addNum($1);}
		| ID LPAR ExprList RPAR		{$$ = AST.addNode("FuncCall",AST.addNode($1, NULL, NULL),$3);
									//FINISH NodeType
									}
		| ID LBRA NUMBER RBRA   {
								cout << ">> ID[]\n";
								string idArray = cBS($1) + "[" + to_string($3) + "]";
								$$ = AST.addNode(idArray, NULL, NULL);
								}
;


ExprList: %empty				{$$ = NULL;}
			| Expr				{$$ = $1;}
			| Expr COMMA ExprList {$$ = AST.addNode("ExprList",$1,$3);
											//FINISH
			}
;
%%

int main(int argc, char**argv)
{
/*
	#ifdef YYDEBUG
		yydebug = 1;
	#endif
*/
	printf("\n\n##### COMPILER STARTED #####\n\n");
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();
	AST.printTree(AST.root,0);
	openIRFile();
	AST.genIR(AST.root);
	closeIRFile();
	openASMFile();
	ASMGen();
	closeASMFile();
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
