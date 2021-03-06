

%{
#include "y.tab.h" 
#include<stdio.h>

%}


alpha [a-zA-Z]
digit [0-9]

%%

"abstract" return KEYWORD; 
"alignof" return KEYWORD;
"as" return KEYWORD;
"become" return KEYWORD;
"box" return KEYWORD;
"break" return KEYWORD;
"const" return KEYWORD;
"continue" return KEYWORD;
"crate" return KEYWORD;
"do" return KEYWORD;
"else" return else1;
"enum" return KEYWORD;
"extern" return KEYWORD;
"false" return KEYWORD;
"final" return KEYWORD;
"fn" return KEYWORD;
"for" return for1;
"if" return if1;
"impl" return KEYWORD;
"in" return KEYWORD;
"let"  return let;
"loop" return KEYWORD;
"macro" return KEYWORD;
"main" return KEYWORD;
"println" return KEYWORD;
"match" return KEYWORD;
"mod" return KEYWORD;
"move" return KEYWORD;
"mut" return KEYWORD;
"offsetof" return KEYWORD;
"override" return KEYWORD;
"priv" return KEYWORD;
"proc" return KEYWORD;
"pub" return KEYWORD;
"pure" return KEYWORD;
"ref" return KEYWORD;
"return" return KEYWORD;
"Self" return KEYWORD;
"self" return KEYWORD;
"sizeof" return KEYWORD;
"static" return KEYWORD;
"struct" return KEYWORD;
"super" return KEYWORD;
"trait" return KEYWORD;
"true" return KEYWORD;
"type" return KEYWORD;
"typeof" return KEYWORD;
"unsafe" return KEYWORD;
"unsized" return KEYWORD;
"use" return KEYWORD;
"virtual" return KEYWORD;
"where" return KEYWORD;
"while" return while1;
"yield" return KEYWORD;

["+"|"-"][0-9]{digit}*"."[0-9]{digit}* {  yylval.str=strdup(yytext);    return FLOAT;  }
[0-9]{digit}*"."[0-9]{digit}* {   yylval.str=strdup(yytext);    return FLOAT; }


[1-9]{digit}* {   yylval.str=strdup(yytext);   return INTEGER; }
["+"|"-"][1-9]{digit}* {   yylval.str=strdup(yytext);  return INTEGER;}





"&&" return LOP;
"|||" return LOP;
"||" return LOP;

"<" 	{yylval.str = strdup(yytext);	return RELOP;}
"==" 	{yylval.str = strdup(yytext);	return RELOP;}
"<=" 	{yylval.str = strdup(yytext); 	return RELOP;}
">" 	{yylval.str = strdup(yytext);	return RELOP;}
">=" 	{yylval.str = strdup(yytext);	return RELOP;}



"\"".*"\"" return STRING;

{alpha}({alpha}|{digit})* {   yylval.str = strdup(yytext); return IDENTIFIER;}

[ \n\t\r]+   

. return yytext[0];
%%


