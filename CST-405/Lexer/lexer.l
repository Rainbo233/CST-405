%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()

int words = 0;
int chars = 0;
int lines = 0;

%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit}|_)*
delim       [ \t\n]
NUMBER         {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
ws          {delim}+

%%
"/*"    				{
							int c;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/')
										break;
									else
										unput(c);
								}
							}
						}
			
"if"	{words++; chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
		}

"else"	{words++; chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
		}
"while"	{words++; chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
		}
"break"	{words++; chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
		}
						
"int"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		}

"char"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		}
		
"write"	{words++; 
		 chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
		}
"read"	{words++; 
		 chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
		}		
			
{ID}	{words++; chars += strlen(yytext);
		 printf("%s : IDENTIFIER\n",yytext);
		}
			

{NUMBER} {
    words++;
    chars += strlen(yytext);
    if (strchr(yytext, '.') != NULL) {
        printf("%s : FLOAT\n", yytext);
    } else {
        printf("%s : NUMBER\n", yytext);
    }
}


\".*\" { 
    chars += strlen(yytext);
    printf("%s : string\n", yytext);
}


">="	{chars++;
		 printf("%s : OP\n", yytext);
		}

"<="	{chars++;
		 printf("%s : OP\n", yytext);
		}

">"		{chars++;
		 printf("%s : Greaterthan_OP\n", yytext);
		}

"<"		{chars++;
		 printf("%s : Lessthan_OP\n", yytext);
		}

"=="	{chars++;
		 printf("%s : OP\n", yytext);
		}

"!="	{chars++;
		 printf("%s : OP\n", yytext);
		}

"&&"	{chars++;
		 printf("%s : OP\n", yytext);
		}

"||"	{chars++;
		 printf("%s : both_OP\n", yytext);
		}

"+"		{chars++;
		 printf("%s : addition_OP\n", yytext);
		}

"-"		{chars++;
		 printf("%s : Minus_OP\n", yytext);
		}

"*"		{chars++;
		 printf("%s : multiplication_OP\n", yytext);
		}

"/"		{chars++;
		 printf("%s : OP\n", yytext);
		}
"["    {chars++;
		 printf("%s : Lbracket_OP\n", yytext);
		}  

"]" 	{chars++;
		 printf("%s : Rbracket_OP\n", yytext);
		}                   
"{" 	{chars++;
		 printf("%s : LcurlyBraket_OP\n", yytext);
		} 
"}" 	{chars++;
		 printf("%s : RcurlyBraket_OP\n", yytext);
		} 
";"		{chars++;
		 printf("%s : SEMICOLON\n", yytext);
		}
"="		{chars++;
		 printf("%s : equal_OP\n", yytext);
		}
"!"		{chars++;
		 printf("%s : OP\n", yytext);
		}
"("		{chars++;
		 printf("%s : Lparenthesis_OP \n", yytext);
		}
")"		{chars++;
		 printf("%s : Rparenthesis_OP\n", yytext);
		}
","		{chars++;
		 printf("%s : comma \n", yytext);
		}
"()"|"( )"   { 
    chars++;
    printf("%s : doubleparenthesis_op \n", yytext);
}

\n		{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		


%%
int main(int argc, char**argv)
{
	#ifdef YYDEBUG
		yydebug = 1;
	#endif

	printf("Compiler started. \n\n");

	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yylex();
}