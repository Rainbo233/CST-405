
// Parser file that turns tokens into a binary tree



%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "CodeGen.h"

BinTree AST;

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* IRfile;

void yyerror(const char* s);
char currentScope[50]; // function name that passes through from symbol table
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
// list of tokens to identify

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
											
}
;

ParamDeclList: %empty				{$$ = NULL;}
			| ParamDecl				{$$ = $1;}
			| ParamDecl COMMA ParamDeclList {$$ = AST.addNode("ParamDeclList",$1,$3);
											
			}
;

Block: LCBRA BlockList RCBRA {$$ = $2;}
;

BlockList: %empty					{$$ = NULL;}
		| BlockList StmtList		{$$ = AST.addNode("BLockList",$1,$2);
									
									}
		| BlockList VarDecl			{$$ = AST.addNode("BLockList",$1,$2);
									
									}
;

ParamDecl: Type ID					{printf("\n ParamDecl \n");
									$$ = AST.addNode($2, NULL, NULL);
									
									}
		| Type ID LBRA RBRA {$$ = AST.addNode($2, NULL, NULL);}
;

DeclList:	Decl DeclList	{$$ = AST.addNode("DeclList",$1,$2);
							
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
									// The Symbol Table
									symTabAccess();
									int inSymTab = found($2, currentScope);
									
									
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
								printf("HUH? %s\n", $2);
								for (int x = 0; x < $4; x++){
									string n = cBS($2);
									printf("|%s", n);
								}
								$$ = AST.addNode($2,NULL, NULL);
							
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
	| Expr SEMICOLON	{$$ = $1;}
	| WRITE Expr SEMICOLON{$$ = AST.addNode("WRITE",$2,$2);};
	| RETURN Expr SEMICOLON{$$ = AST.addNode("Return",$2,NULL);
							
							}
	| WRITELN SEMICOLON {$$ = AST.addNode("WRITELN",NULL,NULL);
							
							}
;

Expr: Primary 		{$$ = $1;}
	| ID {$$ = AST.addNode($1, NULL, NULL); printf("\n RECOGNIZED RULE: Simplest expression: %s \n", $1); }
	| ID EQ Expr 	{ printf("\n RECOGNIZED RULE: Assignment statement\n"); 
					
					  $$ = AST.addNode("=",AST.addNode($1, NULL, NULL),$3);
					
					if(found($1, currentScope) != 1){
						printf("Semantic error: Variable %s has not been declared in scope %s \n", $1, currentScope);
						semanticCheckPassed = 0;
					}

					if(found($3->data, currentScope) != 1){
						printf("Semantic error: Variable %s has not been declared in scope %s \n", $3, currentScope);
						semanticCheckPassed = 0;
					}

					printf("\nChecking types: \n");
					int typeMatch = compareTypes ($1, $3->data, currentScope);
					if (typeMatch == 0){
						printf("Semantic error: Type mismatch for variables %s and %s \n", $1, $3);
						semanticCheckPassed = 0;
					}

					if (semanticCheckPassed == 1){
						printf("\n\n >IR code is emitted!<\n\n");
				
					}
				
				}
	| Expr MULT Expr	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("*",$1,$3);
				}
	| ID MULT Expr	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("*",AST.addNode($1, NULL, NULL),$3);
				}	
	| ID MULT ID	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("*",AST.addNode($1, NULL, NULL),AST.addNode($3, NULL, NULL));
				}	
	| ID MULT NUMBER	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("*",AST.addNode($1, NULL, NULL),AST.addNum($3));
				}	
	| NUMBER MULT NUMBER	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("*",AST.addNum($1),AST.addNum($3));
				}	
	| Expr PLUS Expr	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("+",$1,$3);
				}
	| ID PLUS Expr	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("+",AST.addNode($1, NULL, NULL),$3);
				}	
	| ID PLUS ID	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("+",AST.addNode($1, NULL, NULL),AST.addNode($3, NULL, NULL));
				}	
	| ID PLUS NUMBER	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("+",AST.addNode($1, NULL, NULL),AST.addNum($3));
				}	
	| NUMBER PLUS NUMBER	{printf("\n RECOGNIZED RULE: MULT statement\n");
				$$ = AST.addNode("+",AST.addNum($1),AST.addNum($3));
				}	
	| ID EQ Expr 	{ printf("\n RECOGNIZED RULE: Assignment statement\n"); 
					  
					   char str[50];
					   sprintf(str, "%d", $3); 
					   $$ = AST.addNode("=",AST.addNode($1, NULL, NULL), $3);
					}
	| ID LBRA NUMBER RBRA EQ Expr {
								
								$$ = AST.addNode("=",NULL,NULL);
								}
;

Primary: ID						{$$ = AST.addNode($1, NULL, NULL);
								printf("\nPrimary BS \n");
								}
		| NUMBER				{$$ = AST.addNum($1);}
		| ID LPAR ExprList RPAR		{$$ = AST.addNode("FuncCall",AST.addNode($1, NULL, NULL),$3);
									
									}
		| ID LBRA NUMBER RBRA   {$$ = AST.addNode("Array",NULL,NULL);
								
								}
;


ExprList: %empty				{$$ = NULL;}
			| Expr				{$$ = $1;}
			| Expr COMMA ExprList {$$ = AST.addNode("ExprList",$1,$3);
										
			}
;
%%

int main(int argc, char**argv)
{

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