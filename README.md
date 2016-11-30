# Implementation of Mozilla Rust Language Compiler

We have implemented the lexing, parsing, and intermediate code generation phases of a compiler for the Mozilla Rust programming language. 

The lexing phase involves converting a Rust program into a sequence of tokens. The parser then processes this stream of tokens and with the help of the first and follow sets, checks whether the sample program satisifes the syntax rules of the Rust language grammer.

The intermediate code generation phase generates intermediate code in the form of three address code (3AC) with the help of Lex and YACC.

For the purpose of this project, we have tried to cover all simple programming constructs such as arithmetic expressions, conditional statement and loops.

A detailed explanation of the Rust grammer can be seen at https://doc.rust-lang.org/grammar.html

## Getting Started

The Lexing and Parsing phases are impemented as simple C programs. The Intermediate Code Generation phase is implemented with the help of Lex and YACC. The entire project was run on Ubuntu environment.

### Lexer and Parser

The code and data for the lexing and parsing phase is present in the folder named "Lexer_Parser". 

lexer.c takes the name of the rust program file as a command line argument and prints the list of tokens into the file output.txt. The exact tokens identified by the program are present in the folders aop.txt (arithmetic operatos), lop.txt (logical operators), keywords.txt, delimiters.txt, delims.txt (delimiters), and relop.txt (relational operators).

parser.c takes the stream of tokens in output.txt and uses the grammer rules (rules.txt) and the first and follow sets (first_follow.xlsx) and prints to console whether the program is acceptd by the language grammer or whether it has syntactical errors.

Order of Execution (command line):
gcc lexer.c -o Lexer
./Lexer <sample_progam>.rs
gcc parser.c -o Parser
./Parser

Sample Rust programs with which we ran ran our code are present in the TestCases folder.  

### Intermediate Code Generation

The code and data for this phase are present in the folder named "ICG"

Installing Lex and Yacc

Lex can be installed through command line (in Ubuntu environment) as follows:
sudo apt-get install flex

Yacc can be installed through command line (in Ubuntu environment) as follows:
sudo apt-get install bison

Order of Execution (command line):

lex final.l
yacc -d final.y
gcc y.tab.c -ll -ly -o ICG
./ICG <sample_program>.rs

2 sample Rust progams (sample.rs and sample2.rs) are provided for reference.

## Authors

* **Aditya Nadimpalli** 
* **Sree Nihit Munakala** 
