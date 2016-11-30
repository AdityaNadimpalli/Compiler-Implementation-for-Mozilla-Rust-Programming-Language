
#include<stdio.h>
#include<stdlib.h>

#define SIZE 50

int eflag = 0;
int stack[100];
int top = -1;
char *Tokens[100] =
{"PROGRAM",
"STMTS",
"X1",
"STMT",
"DECL",
"ASSIGN",
"X2",
"EXPRESSION",
"E1",
"TERM",
"LOOP",
"FOR",
"WHILE",
"BOOLEAN",
"EXTEND",
"BTERM",
"NUMBER",
"X7",
"X9",
"X6",
"LITERAL",
"PRINT",
"COND",
"X10",
//Terminals Henceforth
//Terminals Henceforth
//Terminals Henceforth
"IDENTIFIER",
"for",
"while",
"let",
"KEYWORD",
"(",	
")",
"{",
"}",
";",
"!",
",",
"/",
"LOP",
"AOP",
"RELOP",
"if",
"else",
"FLOAT",
"INTEGER",
"STRING",
"$",
"NULL",
"=",
"==",
"."};


int mapping[SIZE][SIZE];

void push(int num)
{
	if(top==-1)
	{
		top = 0;
		stack[top] = num;
	}
	else
	{
		top++;
		stack[top] = num;
	}
}

void pop()
{
	if(top==-1)
		return;
	top--;
}

void show()
{

	if(top==-1)
		return;

	printf("Stack:\n");
	int i = top;	
	while(i>=0)
	{
		if(stack[i]==46)
		{	
			i--;
			continue;
		}

		//printf("%d: ",stack[i]);
		printf("       %s\n",Tokens[stack[i--]]);
	}
	printf("\n");
}


// 24 Non terminal
// 21 Terminals
int main()
{

	int p = 0;
	int d = 0;
	for(p=0;p<SIZE;p++)
	for(d=0;d<SIZE;d++)
	{
		mapping[p][d]=-1;
		//printf("%d",mapping[p][d]);
	}

//Create the mapping. Rules sourced from first_follow.xls

//PROGRAM | KEYWORD
mapping[0][28]=0;
//PROGRAM SYNCH $
mapping[0][45]=-111;

//1 STMTS STMT X1  | let
mapping[1][27]=1;
//1 STMTS STMT X1  ;| IDENTIFIER
mapping[1][24]=1;
//1 STMTS STMT X1  | for
mapping[1][25]=1;
//1 STMTS STMT X1 | while
mapping[1][26]=1;
//1 STMTS STMT X1 | if
mapping[1][40]=1;
//1 STMTS STMT X1 | KEYWORD
mapping[1][28]=1;
//STMTS SYNCH }
mapping[1][32]=-111;

//3 X1 STMTS | IDENTIFIER
mapping[2][24]=3;
//3 X1 STMTS | let
mapping[2][27]=3;
//3 X1 STMTS | for
mapping[2][25]=3;
//3 X1 STMTS | while
mapping[2][26]=3;
//3 X1 STMTS | if
mapping[2][40]=3;
//3 X1 STMTS | KEYWORD
mapping[2][28]=3;
//2 X1 NULL | }
mapping[2][32]=2;

//4 STMT DECL | let
mapping[3][27]=4;
//5 STMT ASSIGN ; | IDENTIFIER
mapping[3][24]=5;
//6 STMT LOOP | while
mapping[3][26]=6;
//6 STMT LOOP | for
mapping[3][25]=6;
//7 STMT COND | if
mapping[3][40]=7;
//8 STMT PRINT |KEYWORD
mapping[3][28]=8;
//STMT SYNCH }
mapping[3][32]=-111;


//9 DECL let X2 | let
mapping[4][27]=9;
//DECL SYNCH KEYWORD
mapping[4][28]=-111;
//DECL SYNCH IDENTIFIER
mapping[4][24]=-111;
//DECL SYNCH if
mapping[4][40]=-111;
//DECL SYNCH }
mapping[4][32]=-111;
//DECL SYNCH for
mapping[4][25]=-111;
//DECL SYNCH while
mapping[4][26]=-111;

//12 ASSIGN IDENTIFIER = EXPRESSION | IDENTIFIER
mapping[5][24]=12;
//ASSIGN SYNCH ;
mapping[5][33]=-111;

//10 X2 IDENTIFIER = LITERAL ; | IDENTIFIER
mapping[6][24]=10;
//11 X2 KEYWORD IDENTIFIER = LITERAL ; | KEYWORD
mapping[6][28]=11;
//X2 SYNCH if
mapping[6][40]=-111;
//X2 SYNCH }
mapping[6][32]=-111;
//X2 SYNCH for
mapping[6][25]=-111;
//X2 SYNCH while
mapping[6][26]=-111;
//X2 SYNCH let
mapping[6][27]=-111;

//13 EXPRESSION TERM E1 | IDENTIFIER
mapping[7][24]=13;
//13 EXPRESSION TERM E1 | (
mapping[7][29]=13;
//13 EXPRESSION TERM E1 | FLOAT
mapping[7][42]=13;
//13 EXPRESSION TERM E1 | INTEGER
mapping[7][43]=13;
//EXPRESSION SYNCH )
mapping[7][30]=-111;
//EXPRESSION SYNCH RELOP
mapping[7][39]=-111;
//EXPRESSION SYNCH LOP
mapping[7][37]=-111;
//EXPRESSION SYNCH {
mapping[7][31]=-111;

//15 E1 AOP TERM E1 | AOP
mapping[8][38]=15;
//14 E1 NULL  | )
mapping[8][30]=14;
//14 E1 NULL  | {
mapping[8][31]=14;
//14 E1 NULL  | LOP
mapping[8][37]=14;
//14 E1 NULL  | RELOP
mapping[8][39]=14;
//14 E1 NULL  | )
mapping[8][30]=14;
//14 E1 NULL  | ;
mapping[8][33]=14;

//17 TERM IDENTIFIER | IDENTIFIER
mapping[9][24]=17;
//16 TERM ( EXPRESSION ) | (
mapping[9][29]=16;
//18 TERM NUMBER | FLOAT
mapping[9][42]=18;
//18 TERM NUMBER | INTEGER
mapping[9][43]=18;
//TERM SYNCH AOP
mapping[9][38]=-111;
//TERM SYNCH )
mapping[9][30]=-111;
//TERM SYNCH RELOP
mapping[9][39]=-111;
//TERM SYNCH LOP
mapping[9][37]=-111;
//TERM SYNCH }
mapping[9][31]=-111;
//TERM SYNCH ;
mapping[9][33]=-111;

//19 LOOP FOR | for
mapping[10][25]=19;
//20 LOOP WHILE | while
mapping[10][26]=20;
//LOOP SYNCH KEYWORD
mapping[10][28]=-111;
//LOOP SYNCH IDENTIFIER
mapping[10][24]=-111;
//LOOP SYNCH if
mapping[10][40]=-111;
//LOOP SYNCH }
mapping[10][31]=-111;
//LOOP SYNCH let
mapping[10][27]=-111;

//21 FOR for IDENTIFIER KEYWORD INTEGER . . . INTEGER { STMTS } | for
mapping[11][25]=21;
//FOR SYNCH KEYWORD
mapping[11][28]=-111;
//FOR SYNCH IDENTIFIER
mapping[11][24]=-111;
//FOR SYNCH if
mapping[11][40]=-111;
//FOR SYNCH }
mapping[11][31]=-111;
//FOR SYNCH let
mapping[11][27]=-111;
//FOR SYNCH while
mapping[11][26]=-111;

//22 WHILE while BOOLEAN { STMTS } | while
mapping[12][26]=22;
//WHILE SYNCH KEYWORD
mapping[12][28]=-111;
//WHILE SYNCH IDENTIFIER
mapping[12][24]=-111;
//WHILE SYNCH if
mapping[12][40]=-111;
//WHILE SYNCH }
mapping[12][31]=-111;
//WHILE SYNCH let
mapping[12][27]=-111;
//WHILE SYNCH for
mapping[12][25]=-111;

//34 BOOLEAN BTERM X7 | IDENTIFIER
mapping[13][24]=34;
//34 BOOLEAN BTERM X7 | (
mapping[13][29]=34;
//34 BOOLEAN BTERM X7 | !
mapping[13][34]=34;
//34 BOOLEAN BTERM X7 | FLOAT
mapping[13][42]=34;
//34 BOOLEAN BTERM X7 | INTEGER
mapping[13][43]=34;
//BOOLEAN SYNCH {
mapping [13][31]=-111;
//BOOLEAN SYNCH )
mapping [13][30]=-111;

//31 EXTEND IDENTIFIER X6 | IDENTIFIER
mapping[14][24]=31;
//EXTEND SYNCH )
mapping [14][30]=-111;

//37 BTERM EXPRESSION RELOP EXPRESSION | IDENTIFIER
mapping[15][24]=37;
//38 BTERM ! BTERM | !
mapping[15][34]=38;
//37 BTERM EXPRESSION RELOP EXPRESSION | FLOAT
mapping[15][42]=37;
//37 BTERM EXPRESSION RELOP EXPRESSION | INTEGER
mapping[15][43]=37;
//BTERM SYNCH LOP
mapping[15][37]=-111;
//BTERM SYNCH {
mapping[15][31]=-111;
//BTERM SYNCH )
mapping[15][30]=-111;

//40 NUMBER FLOAT | FLOAT
mapping[16][42]=40;
//39 NUMBER INTEGER | INTEGER
mapping[16][43]=39;
//NUMBER SYNCH AOP
mapping[16][38]=-111;
//NUMBER SYNCH )
mapping[16][30]=-111;
//NUMBER SYNCH RELOP
mapping[16][39]=-111;
//NUMBER SYNCH LOP
mapping[16][37]=-111;
//NUMBER SYNCH {
mapping[16][31]=-111;

//36 X7 LOP BTERM | LOP
mapping[17][37]=26;
//35 X7 NULL | )
mapping[17][30]=35;
//35 X7 NULL | {
mapping[17][31]=35;

//30 X9 ) ; | )
mapping[18][30]=30;
//29 X9 , EXTEND ) ; | ,
mapping[18][35]=29;
//X9 SYNCH KEYWORD
mapping[18][28]=-111;
//X9 SYNCH IDENTIFIER
mapping[18][24]=-111;
//X9 SYNCH if
mapping[18][40]=-111;
//X9 SYNCH }
mapping[18][31]=-111;
//X9 SYNCH let
mapping[18][27]=-111;
//X9 SYNCH while
mapping[18][26]=-111;
//X9 SYNCH for
mapping[18][25]=-111;

//32 X6 NULL | )
mapping[19][30]=32;
//33 X6 , EXTEND | ,
mapping[19][35]=323;

//26 LITERAL NUMBER | FLOAT
mapping[20][42]=26;
//26 LITERAL NUMBER | INTEGER
mapping[20][43]=26;
//27 LITERAL " STRING | "
mapping[20][36]=27;
//LITERAL SYNCH ;
mapping[20][33]=-111;

//28 PRINT KEYWORD ! ( " STRING " X9 | KEYWORD
mapping[21][28]=28;
//PRINT SYNCH IDENTIFIER
mapping[21][24]=-111;
//PRINT SYNCH if
mapping[21][40]=-111;
//PRINT SYNCH }
mapping[21][31]=-111;
//PRINT SYNCH let
mapping[21][27]=-111;
//PRINT SYNCH while
mapping[21][26]=-111;
//PRINT SYNCH for
mapping[21][25]=-111;

//23 COND if BOOLEAN { STMTS } X10 | if
mapping[22][40]=23;
//COND SYNCH KEYWORD
mapping[22][28]=-111;
//COND SYNCH IDENTIFIER
mapping[22][24]=-111;
//COND SYNCH }
mapping[22][31]=-111;
//COND SYNCH let
mapping[22][27]=-111;
//COND SYNCH while
mapping[22][26]=-111;
//COND SYNCH for
mapping[22][25]=-111;

//25 X10 else { STMTS } | else
mapping[23][41]=25;
//24 X10 NULL | IDENTIFIER    
mapping[23][24]=24;
//24 X10 NULL | for
mapping[23][25]=24;
//24 X10 NULL | while
mapping[23][26]=24;
//24 X10 NULL | let
mapping[23][27]=24;
//24 X10 NULL | KEYWORD    
mapping[23][28]=24;
//24 X10 NULL | }
mapping[23][32]=24;
//24 X10 NULL | if
mapping[23][40]=24;


////////////////////////

	int input[500];
	//Get the file to parse
	FILE* f1 = fopen("output.txt","r");
	int i,k,s = 0;
	char temp[100];
	while(fscanf(f1,"%s",temp)!=EOF)
	{
		for(s=0;s<SIZE;s++)
		{
		
			if(strcmp(temp,Tokens[s])==0)
			{
				printf("%s: %d\n ",temp,s);
				input[k++]=s;
//				printf("%d\n",numbuff[k-1]);
				break;
			}
		}	
	}
	
	//Add dollar sign at the end
	input[k++]=45;

/*	while(fscanf(f1,"%d",&input[i++])!=EOF)
	{
		printf("%d\n",input[i-1]);
	}*/

	//Push $ and then PROGRAM onto the stack
	push(45);
	push(0);


	//Peform the parsing
	int index = 0;
	int flag = 1;
	while(flag)
	{

		printf("\n\nInput string: ");
		for(i=index;i<k;i++)
		{
			if(i==46)
				continue;
			printf("%s ",Tokens[input[i]] );

		}
		printf("\n");
	
		show();
		if(stack[top]==46)
		{
			pop();
			continue;
		}

		if(stack[top]==45 && input[index]==45)
		{
			if(eflag==1)			
				printf("Accepted with ERRORS.\n");		
			else
				printf("Accepted!\n");				
			flag = 0;
			break;
		}

		

		//Check if stack and input terminals match - pop and delete
		if(input[index] == stack[top])
		{
			printf("Popping '%s'\n",Tokens[input[index]]);
			index++;	
			pop();
			continue;
		}



		FILE* f2 = fopen("rules.txt","r");

		if(index==k)
		{
			printf("String Empty. Unable to Parse!\n");
			exit(0);
		}

		int lookup = mapping[ stack[top] ][ input[index] ];
		printf("Lookup value for [%d][%d]: %d\n",stack[top],input[index],lookup);

		if(lookup == -1)
		{	eflag = 1;
			printf("Error: %d! Skipping input. \n",input[index]);
			index++;
			continue;
		}

		if(lookup == -111)
		{
			eflag = 1;
			printf("Error: %d! Popping stack. \n",stack[top]);
			pop();
			continue;
		}

		char buffer[100];
		//int line = 0;
		while(fscanf(f2,"%s",buffer)!=EOF)
		{
			if(atoi(buffer)==lookup)
				break;
		}
		//fgets(buffer,100, f2);	

		int numbuff[10];
		int k = 0;
		int fg = 1;

		printf("Using rule: ");
		while(fscanf(f2,"%s",buffer)!=EOF)
		{
			if(atoi(buffer)!=0)
			{
				//printf("%s ",buffer);
				pop();
				k--;
				while(k>=1)
				{
					//printf("%d \n",numbuff[k--]);
					push(numbuff[k--]);
				}
				break;
			}
	//		printf("%s\n",buffer);

			int s = 0;
			for(s=0;s<SIZE;s++)
			{
			
				if(strcmp(buffer,Tokens[s])==0)
				{
					printf("%s ",buffer);
					if(fg==1)
					{
						printf("-> ");
						fg = 0;
					}
					numbuff[k++]=s;
	//				printf("%d\n",numbuff[k-1]);
					break;
				}
			}			
		}
		
			
	}

}
