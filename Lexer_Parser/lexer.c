	#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *output;

void categorise(char buffer[])
{
    
	
    char temp[100];
    if(strcmp(" ",buffer)==0 || strcmp("\n",buffer)==0 || buffer[0]=='\0')
    {
        //printf("here\n");
        return;
    }

    else
    {
        //Check for keywords
        FILE *keywords = fopen("keywords.txt","r");
        while((fgets(temp, 100, keywords))!=NULL)
        {
            int x  = strlen(temp);
		//printf("\n%d\n",x);
            temp[x-1]='\0';
            //printf("%s",temp);
		//printf("%s\n",temp);
		int l1 = strlen(temp);
		int l2 = strlen(buffer);

		//printf("%d vs. %d\n",l1,l2);

		

            if((temp[0] == buffer[0]) && (temp[1] == buffer[1]) )
            {
		printf("\n%s vs. %s\n",temp, buffer);
                if(strcmp(buffer,"let")==0)
                    fprintf(output,"%s\n",buffer);

                else if(strcmp(buffer,"for")==0)
                    fprintf(output,"%s\n",buffer);

                else if(strcmp(buffer,"while")==0)
                     fprintf(output,"%s\n",buffer);

                else if(strcmp(buffer,"if")==0)
                     fprintf(output,"%s\n",buffer);

                else if(strcmp(buffer,"else")==0)
                     fprintf(output,"%s\n",buffer);

                else
                    fprintf(output,"KEYWORD\n");

                return;
            }
        }

        //Check if arithmetic operators
       FILE *aop = fopen("aop.txt","r");
        while((fgets(temp, 100,aop))!=NULL)
        {
            int x  = strlen(temp);
            temp[x-1]='\0';
            //printf("%s",temp);

            if(temp[0]==buffer[0])
            {
                fprintf(output,"AOP\n");
                return;
            }
        }

     //Check for logical operators
       FILE *lop = fopen("lop.txt","r");
        while((fgets(temp, 100,lop))!=NULL)
        {
            int x  = strlen(temp);
            temp[x-1]='\0';
            //printf("%s",temp);

            if(temp[0]==buffer[0])
            {
                fprintf(output,"LOP\n");
                return;
            }
        }

     


    FILE *delims = fopen("delims.txt","r");
        while((fgets(temp, 100,delims))!=NULL)
        {
        	
		int x  = strlen(temp);
            temp[x-1]='\0';

            if(temp[0]==buffer[0])
            {
		//printf("Trying to print Semicolon: %s",buffer);
		if(buffer[0]=='=')
		{
			if(buffer[1]=='=')    
				fprintf(output,"RELOP\n");
			else            	
				fprintf(output,"%s\n",buffer);
		}
		else
			fprintf(output,"%s\n",buffer);                
		return;
            }
        }




	//Check if relational operators
       FILE *relop = fopen("relop.txt","r");
        while((fgets(temp, 100,relop))!=NULL)
        {
            int x  = strlen(temp);
            temp[x-1]='\0';
            //printf("%s\n",temp);

            if((temp[0]==buffer[0]))
            {
                fprintf(output,"RELOP\n");
                return;
            }
        }
//////////////////////////////////////////////////////////////////////



      //  int check_integer = atoi(buffer);
      int k = 0,f=0;
      while(k<strlen(buffer))
      {
          if(k==0)
          {
              if(buffer[k]=='+' || buffer[k]=='-')
                {
                    k++;
                    continue;
                }
          }

          if(!isdigit(buffer[k]))
          {
              f =1;
          }
          k++;
      }

        if(f == 0)
        {
            if(strstr(buffer, ".") != NULL) {
                /* ... */
            }
            else{

            fprintf(output,"INTEGER\n");
            return;
            }
        }
        else
        {
            if(strcmp("0",buffer)==0)
                {
                fprintf(output,"INTEGER\n");
                return;
                }
        }

        k = 0;
        f = 0;
        int f2 = 0, f3 = 0;
        if(!isdigit(buffer[0]) && (buffer[0]!='+') && (buffer[0]!='-'))
            f3=1;
        while(k<strlen(buffer))
      {
          if(k==0)
          {
              if(buffer[k]=='+' || buffer[k]=='-')
                {
                    k++;
                    continue;
                }
          }

            if(!isdigit(buffer[k]))
          {
              if(buffer[k]!='.')
              f =1;
              else if(f2==1)
              f3 =1;
              else
              f2 =1;
          }
          k++;
      }

        //cHECK FOR FLOAT
        float check_float = atof(buffer);
        if(check_float!=0.0)
        if(f3==0 && f == 0)
        {
            //printf("atof gave: %f",check_float);
            fprintf(output,"FLOAT\n");
            return;
        }
        else
        {
            if(strcmp("0.0",buffer)==0)
                {
                fprintf(output,"FLOAT\n");
                return;
                }
        }

        if(!isalpha(buffer[0]) && buffer[0]!='_')
            {
               // printf("Error: %s \n", buffer);
                return;
            }
        else
        {
            int j;
            int flag10 = 0;
            for(j = 0;j<strlen(buffer);j++)
                {
                    if(!isalnum(buffer[j]) && buffer[j]!='_' )
                    {
                        printf("Error: %s \n", buffer);
                        return;
                    }

                }

                 fprintf(output,"IDENTIFIER\n");
        }
    }





}

void string_literal(char *buffer)
{

   
    if(strcmp(" ",buffer)==0 || strcmp("\n",buffer)==0)
    {
        return;
    }

    else

        fprintf(output,"STRING\n");
	



}



int main(int argc, char* args[])
{

output = fopen("output.txt","a");

    FILE *ll = fopen("output.txt","w");
    //fclose(ll);

	


    FILE *input = fopen(args[1],"r");
    FILE *delimiters;
    char *buffer = (char *)malloc(1000*sizeof(char));
    char current;
    int i =0;
    char next;

    while((current=fgetc(input))!=EOF)
    {
        //printf("%c\n",current);
        delimiters = fopen("delimiters.txt","r");
        if(current==' ' || current=='\n'||current=='\t')
        {
                //token
                buffer[i++]='\0';
                printf("detected: %s \n",buffer);
                categorise(buffer);
                free(buffer);
                buffer = (char *)malloc(1000*sizeof(char));
                i=0;
                //printf("Found token %c\n",current);
        }


        // Check for string token
        else if(current=='"')
        {
              if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

            buffer[0]='"';
            buffer[1]='\0';
            printf("detected: %s \n",buffer);
            categorise(buffer);
            free(buffer);
            buffer = (char *)malloc(1000*sizeof(char));
            i=0;

            while((current=fgetc(input))!=EOF)
            {
                 if(current=='"')
               {
                   //== token
                    if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        string_literal(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    //token for "
                    buffer[0]='"';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    i=0;
                    break;
               }
               else
               {
                   buffer[i++]=current;
               }

            }
        }

        //takes care of = and ==
        else if(current == '=')
        {
            char x1 = current;
            char x2;
            if((current=fgetc(input))!=EOF)
            {
                x2 = current;
                if(current=='=')
               {
                   //== token
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    //token for ==
                    buffer[0]='=';
                    buffer[1]='=';
                    buffer[2]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    i=0;

                    if((current = getc(input))!=EOF)
                    {
                        if(current == '+' || current == '-')
                        {
                            buffer[i++] = current;
                        }
                        else
                             fseek(input, -1, SEEK_CUR);
                    }

               }

               else if (current == '+' || current == '-')
               {
                    if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='=';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;
                    buffer[i++]=current;
               }

               else
               {
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='=';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;
                     fseek(input, -1, SEEK_CUR);
                    continue;
               }
            }
        }

    //takes care of < and <=
        else if(current == '<')
        {
            char x1 = current;
            char x2;
            if((current=fgetc(input))!=EOF)
            {
                x2 = current;
                if(current=='=')
               {
                   //== token
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    //token for ==
                    buffer[0]='<';
                    buffer[1]='=';
                    buffer[2]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    i=0;

                    if((current = getc(input))!=EOF)
                    {
                        if(current == '+' || current == '-')
                        {
                            buffer[i++] = current;
                        }
                        else
                             fseek(input, -1, SEEK_CUR);
                    }

               }

               else if (current == '+' || current == '-')
               {
                    if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='<';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;
                    buffer[i++]=current;
               }

               else
               {
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='<';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;
                     fseek(input, -1, SEEK_CUR);
                    continue;
               }
            }
        }

    //takes care of > and >=
        else if(current == '>')
        {
            char x1 = current;
            char x2;
            if((current=fgetc(input))!=EOF)
            {
                x2 = current;
                if(current=='=')
               {
                   //== token
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    //token for ==
                    buffer[0]='>';
                    buffer[1]='=';
                    buffer[2]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    i=0;

                    if((current = getc(input))!=EOF)
                    {
                        if(current == '+' || current == '-')
                        {
                            buffer[i++] = current;
                        }
                        else
                             fseek(input, -1, SEEK_CUR);
                    }

               }

               else if (current == '+' || current == '-')
               {
                    if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='>';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;
                    buffer[i++]=current;
               }

               else
               {
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='>';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;
                     fseek(input, -1, SEEK_CUR);
                    continue;
               }
            }
        }

    //takes care of ! and !=
        else if(current == '!')
        {
            char x1 = current;
            char x2;
            if((current=fgetc(input))!=EOF)
            {
                x2 = current;
                if(current=='=')
               {
                   //== token
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    //token for ==
                    buffer[0]='!';
                    buffer[1]='=';
                    buffer[2]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    i=0;

                    if((current = getc(input))!=EOF)
                    {
                        if(current == '+' || current == '-')
                        {
                            buffer[i++] = current;
                        }
                        else
                             fseek(input, -1, SEEK_CUR);
                    }

               }


               else
               {
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='!';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;
                     fseek(input, -1, SEEK_CUR);
                    continue;
               }
            }
        }

    //takes care of & and &&
        else if(current == '&')
        {
            if((current=fgetc(input))!=EOF)
            {
                if(current=='&')
               {
                   //== token
                     if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    //token for ==
                    buffer[0]='&';
                    buffer[1]='&';
                    buffer[2]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    i=0;

               }
               else
               {
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    buffer[0]='&';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;

               }
            }
        }

    //takes care of | and ||
        else if(current == '|')
        {
            if((current=fgetc(input))!=EOF)
            {
                if(current=='|')
               {
                   //== token
                      if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }
                    //token for ==
                    buffer[0]='|';
                    buffer[1]='|';
                    buffer[2]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    i=0;

               }
               else
               {
                     if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                    buffer[0]='|';
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                    categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));
                    //printf("Found token %c\n",current);
                    i = 0;

               }
            }
        }



        else
        {
            //delimiters iterate
            char tmp;
            char tmp2;
            int flag = 0;
            while((tmp=fgetc(delimiters))!=EOF)
            {
                if(tmp=='\n' || tmp==' ')
                    continue;

               if(tmp==current)
               {
                   //token found and check for op
                    if(current == '+' || current == '-' ||  current == '*' || current == '/' || current=='(')
                    {
                        tmp2 = current;
                        if((current=getc(input))!=EOF)
                           {
                               if(current == '+' || current == '-')
                               {
                                   if(i>0)
                                    {
                                        buffer[i++]='\0';
                                        printf("detected: %s\n",buffer);
                                        categorise(buffer);
                                        free(buffer);
                                        buffer = (char *)malloc(1000*sizeof(char));
                                        //printf("Found token %c\n",current);
                                        i = 0;
                                    }

                                    buffer[0]=tmp2;
                                    buffer[1]='\0';
                                    printf("detected: %s\n",buffer);
                                    categorise(buffer);
                                    free(buffer);
                                    buffer = (char *)malloc(1000*sizeof(char));
                                    //printf("Found token %c\n",current);
                                    i = 0;

                                    buffer[i++]=current;
                                    flag = 1;
                                    break;
                               }

                                if(i>0)
                                {
                                    buffer[i++]='\0';
                                    printf("detected: %s\n",buffer);
                                    categorise(buffer);
                                    free(buffer);
                                    buffer = (char *)malloc(1000*sizeof(char));
                                    //printf("Found token %c\n",current);
                                    i = 0;
                                }

                                buffer[0]=tmp2;
                                buffer[1]='\0';
                                printf("detected: %s\n",buffer);
                                categorise(buffer);
                                free(buffer);
                                buffer = (char *)malloc(1000*sizeof(char));
                                fseek(input, -1, SEEK_CUR);
                                //printf("Found token %c\n",current);
                                i = 0;
                                flag = 1;
                                break;

                           }
                    }


                    if(i>0)
                    {
                        buffer[i++]='\0';
                        printf("detected: %s\n",buffer);
                        categorise(buffer);
                        free(buffer);
                        buffer = (char *)malloc(1000*sizeof(char));
                       //printf("Found token %c\n",current);
                       i = 0;
                    }

                   buffer[0]=current;
                    buffer[1]='\0';
                    printf("detected: %s\n",buffer);
                   categorise(buffer);
                    free(buffer);
                    buffer = (char *)malloc(1000*sizeof(char));

                   //printf("Found token %c\n",current);
                   i = 0;
                   flag = 1;
                   break;

               }
            }

            if(flag==0)
            {
                buffer[i++]=current;
            }



        }

    }

}
