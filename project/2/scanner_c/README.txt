Time-stamp: <2018-04-01 19:03:40 aronov>

This is a C version of the scanner for SiC.  It's made using lex/flex. It's pretty primitive and breaks most of the rules of software engineering.  There's a function (yylex()) that is the scanner entry point.  Every time you call it, you get the next token.  When it returns 0, it reached end-of-file.  What it returns is the _token number_.  Additional information is passed in the _global_ variable yylval: ID name, or integer literal (constant) value etc.  It's a single global variable that gets overwritten next time you call yylex().

There's also a global variable line_no that stores the current line number (starting at 0? 1? I forget).  Again, it's valid at the current token, hopefully, but will be changed as soon as the scanner proceeds.

A nicer interface would store token values in the token or a global table (as in the textbook) and maybe store line numbers with tokens.  I might implement these, but do not count on it (if someone want to volunteer and implement these and share them with the world, please do).

A more object-oriented interface might be nicer to work with C++, but the current one will work as well.

So:

README.txt -- this file
common.h -- some shared definitions/declarations/#define's
makefile -- make file to built the scanner and the driver
tok.l -- Lex specification for the scanner; uses C; actual scanner is the function yyles()
tok.c -- output Lex when run on tok.l, on my computer
scanner-driver.c -- a simple demonstration of the scanner: opens a file, runs yylex() repeatedly; reports the tokens found
TEST, TEST2, TEST3 -- some test input files for the scanner
TEST-EXHAUSTIVE -- a test file that hopefully contains all possible token types and tests for a number of obvious scanner bugs; it is not really exhaustive
TEST_OUTPUT etc -- the matching outputs; report bugs if you can find them!

WARNING: 

-- if you want to use bison/yacc, you need to remove #defines for the tokens; yacc/bison generate a file, usually called y.tab.h, that contains the definition of all the tokens.

-- my scanner might have bugs.  I found about 10 yesterday.  I fixed all the ones I found.  please report bugs and we will fix them as soon as we can.  report them on Piazza.

-- I have implemented an extension in the scanner that allows you do use "blah" to enter literal strings.  I might change the specification of SiC to allow string literals: this allows for much easier to understand programs.  it should not complicate the compiler much, as MASS already supports literal strings and printing of them.  I have not thought about handling special characters in strings nor have I implemented anything, so just do not use them please. :-)
