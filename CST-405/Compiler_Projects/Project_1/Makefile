all: parser

lexer: lexer.l
	flex lexer.l
	gcc -o lexer lex.yy.c
	./lexer Test.cmm


parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d --graph -x parser.y
	bison --print-datadir
	xsltproc /usr/local/share/bison/xslt/xml2xhtml.xsl parser.xml >parser.html

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser: lex.yy.c parser.tab.c parser.tab.h symbolTable.h AST.h
	g++ -o parser parser.tab.c lex.yy.c
	./parser Test.cmm

clean:
	rm -f parser lexer parser.tab.c lex.yy.c parser.tab.h parser.output
	rm -f parser lexer parser.gv parser.html parser.ps parser.xml lexer_standalone
	> IRcode.txt
	ls -l