%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int n = 1;
int l = 1;

typedef struct TAC{


char code[500];
char tmp[500];




}TAC;

TAC tac[100]; //Array of Structures Storing 3AC code at each node in the parse tree
int current = 0;
char* last_number;
char* last_identifier;

char* Temp(){ //Generate new temporary variables of type "t1"
	
	char num_to_concatinate[10];

	char *newTemp = (char *)malloc(20);
	strcpy(newTemp,"t");
	snprintf(num_to_concatinate, 10,"%d",n);
	strcat(newTemp,num_to_concatinate);
		
	n++;
	return newTemp;
}


char* Label(){ //Generate new labels of type "L1"
	
	char num_to_concatinate[10];

	char *newLabel = (char *)malloc(20);
	strcpy(newLabel,"L");
	snprintf(num_to_concatinate, 10,"%d",l);
	strcat(newLabel,num_to_concatinate);
		
	l++;
	return newLabel;
}








%}

%union {
               
		char *str; //string datatype
		TAC tac;  //structure to hold code and new temporary variable generated at each stage.
		
       }

// Datatype of Non Terminals
%type <str> NUMBER

%type <tac> X2
%type <tac> TERM
%type <tac> EXPRESSION
%type <tac> STMT
%type <tac> DECL
%type <tac> ASSIGN
%type <tac> STMTS
%type <tac> PROGRAM
%type <tac> X1
%type <tac> COND
%type <tac> X10
%type <tac> WHILE
%type <tac> FOR1
%type <tac> LOOP
%type <tac> PRINT
%type <str> LITERAL
%type <tac> BOOLEAN
%type <tac> BTERM
%type <str> X9
%type <str> EXTEND


%left '+' '-'
%left '*' '/'


//terminals
%token <str> INTEGER
%token <str> FLOAT
%token <str> KEYWORD

%token AOP
%token <str> RELOP
%token <str> LOP
%token <str> STRING
%token <str> IDENTIFIER
%token <str> for1
%token while1
%token <str> if1
%token else1
%token let




%%

PROGRAM : KEYWORD KEYWORD '(' ')' '{' STMTS '}'     {

								$$.code[0]='\0';
								$$.tmp[0]='\0';
				
								strcat($$.code,$6.code);
								strcpy($$.tmp,$6.tmp);


								printf("Final code so far: \n%s\n",$$.code);
		

							}
;

STMTS : STMT X1		{
				$$.code[0]='\0';
				$$.tmp[0]='\0';
				
				strcat($$.code,$1.code);
				strcat($$.code,$2.code);
				strcpy($$.tmp,$1.tmp);


			}
;

X1 : 				{$$.code[0]='\0'; $$.tmp[0]='\0';}
| STMTS 			{
					$$.code[0]='\0';
					$$.tmp[0]='\0';
				
					strcat($$.code,$1.code);
					strcpy($$.tmp,$1.tmp);

	
				}
;

STMT : DECL 	{

				$$.code[0]='\0';
				$$.tmp[0]='\0';
				
				strcat($$.code,$1.code);
				strcpy($$.tmp,$1.tmp);


		}      
| ASSIGN ';'		{

				$$.code[0]='\0';
				$$.tmp[0]='\0';
				
				strcat($$.code,$1.code);
				strcpy($$.tmp,$1.tmp);
				
			}
| LOOP 			{

						$$.code[0]='\0';
						$$.tmp[0]='\0';   
						strcat($$.code,$1.code);
						strcpy($$.tmp,$1.tmp);

			}
| COND {                                     

				$$.code[0]='\0';
				$$.tmp[0]='\0';
				
				strcat($$.code,$1.code);
				strcpy($$.tmp,$1.tmp);
				

}
| PRINT
;

DECL : let X2 {
				$$.code[0]='\0';
				$$.tmp[0]='\0';
				
				strcat($$.code,$2.code);
				strcpy($$.tmp,$2.tmp);


			 }
;

X2 : IDENTIFIER '=' INTEGER ';' { 

					$$.code[0]='\0';
					$$.tmp[0]='\0';
					
					char *here=(char *)malloc(100*sizeof(char));	
					snprintf(here, 50,"%s = %s\n",$1,$3);
					strcat($$.code,here);
				
					strcpy($$.tmp,$1);

				 } 
| KEYWORD IDENTIFIER '=' LITERAL ';' {


					$$.code[0]='\0';
					$$.tmp[0]='\0';
					
					char *here=(char *)malloc(100*sizeof(char));	
					snprintf(here, 50,"%s = %s\n",$2,$4);
					strcat($$.code,here);
				
					strcpy($$.tmp,$2);



				}
;

ASSIGN : IDENTIFIER '=' EXPRESSION 		{ 
				
					
							$$.code[0]='\0';
							$$.tmp[0]='\0';
					
							char *here=(char *)malloc(100*sizeof(char));
				
							snprintf(here, 50,"%s = %s\n",$1,$3.tmp);
							if($3.code[0]!='\0')
							strcat($$.code,$3.code);
							strcat($$.code,here);
				
							strcpy($$.tmp,$1);
						 }
;

EXPRESSION : TERM 	{
				$$.code[0]='\0';
				$$.tmp[0]='\0';
			
				char *here=(char *)malloc(100*sizeof(char));
				
				if($1.code[0]!='\0')
				{
					strcat($$.code,$1.code);
					strcpy($$.tmp,$1.tmp);
				
				}

				else{
					strcpy($$.tmp,$1.tmp);	

				}
			
 }


| EXPRESSION '+' EXPRESSION  {

				$$.code[0]='\0';
				$$.tmp[0]='\0';		
			
				char *here=(char *)malloc(100*sizeof(char));
				char *tmp = Temp();
				
				snprintf(here, 50,"%s = %s + %s\n",tmp,$1.tmp,$3.tmp);
				if($1.code[0]!='\0')
					strcat($$.code,$1.code);
				if($3.code[0]!='\0')
					strcat($$.code,$3.code);
				strcat($$.code,here);
				strcpy($$.tmp,tmp);

		 } 
| EXPRESSION '-' EXPRESSION  {

				$$.code[0]='\0';
				$$.tmp[0]='\0';		
			
				char *here=(char *)malloc(100*sizeof(char));
				char *tmp = Temp();
				
				snprintf(here, 50,"%s = %s - %s\n",tmp,$1.tmp,$3.tmp);
				if($1.code[0]!='\0')
					strcat($$.code,$1.code);
				if($3.code[0]!='\0')
					strcat($$.code,$3.code);
				strcat($$.code,here);
				strcpy($$.tmp,tmp);

			}



| EXPRESSION '*' EXPRESSION {

				$$.code[0]='\0';
				$$.tmp[0]='\0';		
			
				char *here=(char *)malloc(100*sizeof(char));
				char *tmp = Temp();
				
				snprintf(here, 50,"%s = %s * %s\n",tmp,$1.tmp,$3.tmp);
				if($1.code[0]!='\0')
					strcat($$.code,$1.code);
				if($3.code[0]!='\0')
					strcat($$.code,$3.code);
				strcat($$.code,here);
				strcpy($$.tmp,tmp);

				
			 } 
| EXPRESSION '/' EXPRESSION {

				$$.code[0]='\0';
				$$.tmp[0]='\0';		
			
				char *here=(char *)malloc(100*sizeof(char));
				char *tmp = Temp();
				
				snprintf(here, 50,"%s = %s / %s\n",tmp,$1.tmp,$3.tmp);
				if($1.code[0]!='\0')
					strcat($$.code,$1.code);
				if($3.code[0]!='\0')
					strcat($$.code,$3.code);
				strcat($$.code,here);
				strcpy($$.tmp,tmp);

				
			


			}
;

TERM : '(' EXPRESSION ')' {
				$$.code[0]='\0';
				$$.tmp[0]='\0';
			
				strcat($$.code,$2.code);
				strcpy($$.tmp, $2.tmp);


				} 	
| IDENTIFIER { 
			$$.code[0]='\0';
			$$.tmp[0]='\0';
			
			strcpy($$.tmp,$1);
			
		}
| NUMBER 	{		


			$$.code[0]='\0';
			$$.tmp[0]='\0';
			
			strcpy($$.tmp,$1);
		
		}
;

LOOP : FOR1 		{

						$$.code[0]='\0';
						$$.tmp[0]='\0';   
						strcat($$.code,$1.code);
						strcpy($$.tmp,$1.tmp);



			}
| WHILE 	{   				$$.code[0]='\0';
						$$.tmp[0]='\0';   
						strcat($$.code,$1.code);
						strcpy($$.tmp,$1.tmp);
						


		}
;

FOR1 : for1 IDENTIFIER KEYWORD INTEGER '.' '.' INTEGER '{' STMTS '}' 
			{

				
							
				$$.code[0]='\0';
				$$.tmp[0]='\0';	

				char *here=(char *)malloc(100*sizeof(char));
				char *next=(char *)malloc(100*sizeof(char));
				char *tmp = Temp();
				char *label1 = Label();
				char *label2 = Label();
				snprintf(here, 500,"%s = %s\n", $2,$4);
				strcat($$.code,here);
				snprintf(next, 500,"%s: if %s > %s goto %s\n%s\nGOTO %s\n%s: ", label1,$2,$7,label2,$9.code,label1,label2);
			
				strcat($$.code,next);
				strcat($$.tmp,$2);

			}

;

WHILE : while1 BOOLEAN '{' STMTS '}'    
				{

					$$.code[0]='\0';
					$$.tmp[0]='\0';
					char *label1 = Label();
					char *next=(char *)malloc(100*sizeof(char));
					snprintf(next, 500,"%s: ", label1);
					strcat($$.code,next);
					char *here=(char *)malloc(100*sizeof(char));						

					char *label2 = Label();				
						
					strcat($$.code,$2.code);
					snprintf(here, 500,"if %s == 0 GOTO %s\n %s\nGOTO %s\n%s:  ", $2.tmp,label2,$4.code,label1,label2);
					strcat($$.code,here);

				}
;

COND : if1 BOOLEAN '{' STMTS '}' X10 
				{  
					
					$$.code[0]='\0';
					$$.tmp[0]='\0';
						
					char *here=(char *)malloc(100*sizeof(char));
					char *next=(char *)malloc(100*sizeof(char));
						
					strcat($$.code,$2.code);
						

					char *label1 = Label();
					char *label2 = Label();
							
					snprintf(here, 500,"if %s == 0 GOTO %s\n %s\n", $2.tmp,label1,$4.code);
					strcat($$.code,here);
			
					if($6.code[0]!='\0')
					{
					
						snprintf(next, 100,"GOTO %s\n%s: %s\n %s: ", label2,label1,$6.code,label2);
						strcat($$.code,next);


					}
					else{
						snprintf(next, 100,"%s: ", label1);
						strcat($$.code,next);
					
					}

						strcpy($$.tmp, $2.tmp);

						

			}
;

X10 :   {  $$.code[0]='\0'; $$.tmp[0]='\0';  }
| else1 '{' STMTS '}' {

						$$.code[0]='\0';
						$$.tmp[0]='\0';	
						strcat($$.code,$3.code);
						strcat($$.tmp, $3.tmp);

			}
;

LITERAL : NUMBER {}
| STRING
;

PRINT : KEYWORD '!' '(' STRING X9 
;

X9 : ',' EXTEND ')' ';'
| ')' ';'
;

EXTEND : IDENTIFIER X6
;

X6 : 
| ',' EXTEND
;

BOOLEAN : BTERM { 

						$$.code[0]='\0';
						$$.tmp[0]='\0';
						

						strcat($$.code,$1.code);
						strcpy($$.tmp, $1.tmp);



			 }
|  BOOLEAN LOP BOOLEAN{ }
;



BTERM : EXPRESSION RELOP EXPRESSION {
				
					$$.code[0]='\0';
					$$.tmp[0]='\0';
						

						char *here=(char *)malloc(100*sizeof(char));
						char *tmp = Temp();
						char *label = Label();
						
				snprintf(here, 100,"if %s %s %s GOTO NXT + 3\n %s = 0\nGOTO NXT + 2\n%s = 1\n", $1.tmp,$2,$3.tmp,tmp,tmp);
				if($1.code[0]!='\0')
					strcat($$.code,$1.code);
				if($3.code[0]!='\0')
					strcat($$.code, $3.code);

				strcat($$.code, here);
				strcpy($$.tmp, tmp);

				 }

;

NUMBER : INTEGER {    }
| FLOAT { }
;

%%

#include"lex.yy.c"
#include <ctype.h>

yyerror()
{
	printf("Not valid.\n");
	return 0;
}


FILE *f1;
int main(int argc, char *argv[])
{	
	yyin = fopen(argv[1], "r");
	f1=fopen("output.txt","w");

	//printf("Parse I guess?\n");

	if(!yyparse())
		printf("\nParsing complete\n");
	else
	{
		printf("\nParsing failed\n");
		exit(0);
	}
	
	fclose(yyin);
	fclose(f1);


}






