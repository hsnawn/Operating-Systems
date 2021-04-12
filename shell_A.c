#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens

*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;

	FILE* fp;
	if(argc == 2) {
		fp = fopen(argv[1],"r");
		if(fp < 0) {
			printf("File doesn't exists.");
			return -1;
		}
	}

	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		if(argc == 2) { // batch mode
			if(fgets(line, sizeof(line), fp) == NULL) { // file reading finished
				break;	
			}
			line[strlen(line) - 1] = '\0';
		} else { // interactive mode
			printf("$ ");
			scanf("%[^\n]", line);
			getchar();
		}
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
		
		if(strcmp(tokens[0],"ls")==0){
	         char *args[2];
                 int status;
                   args[0]="/bin/ls"; 
                   args[1]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args ); 
               else
                  wait( &status ); }
                
               if(strcmp(tokens[0],"pwd")==0){

	         char *args[20];
                 int status;
                 args[0]="/bin/pwd";
                 args[1]=NULL; 
                  
               if ( fork() == 0 )
                  execv( args[0], args );

               else
                  wait( &status ); }
                
               if(strcmp(tokens[0],"cat")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/cat"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;

               if ( fork() == 0 )
                  execv( args[0], args ); \

               else
                  wait( &status ); }
              
               if(strcmp(tokens[0],"echo")==0){
                 i=1;
                 char *args[20];
                 int status;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/echo"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;

               if ( fork() == 0 )
                  execv( args[0], args);
                  
               else
                  wait( &status ); }
                
                
              if(strcmp(tokens[0],"ps")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/ps"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
                
                
              if(strcmp(tokens[0],"sleep")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/sleep"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
              
              
               if(strcmp(tokens[0],"top")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/top"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;

               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
               
               
               if(strcmp(tokens[0],"dir")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/dir"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;

               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
              
              
               if(strcmp(tokens[0],"pidstat")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/pidstat"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;

               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
               
               if(strcmp(tokens[0],"grep")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/grep"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;

               if ( fork() == 0 )
                  execv( args[0], args ); 

               else
                  wait( &status ); }
                
                
               if(strcmp(tokens[0],"df")==0){
	         char *args[20];
                 int status;
		       
                   args[0]="/bin/df"; 
                   args[1]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args );
                  
               else
                  wait( &status ); }
                
                
               if(strcmp(tokens[0],"gzip")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/gzip"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
                
                
               if(strcmp(tokens[0],"find")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/find"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
                 
                 
               if(strcmp(tokens[0],"wget")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/wget"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
                  
                  
               if(strcmp(tokens[0],"kill")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/kill"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args );
                  
               else
                  wait( &status ); }
               
               
               if(strcmp(tokens[0],"mkdir")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 while(tokens[i]!=NULL){
                   args[0]="/bin/mkdir"; 
                   args[i]=tokens[i];
                   i++;
                   }
                 args[i]=NULL;
               if ( fork() == 0 )
                  execv( args[0], args ); 
                  
               else
                  wait( &status ); }
                  
                  
               if(strcmp(tokens[0],"cd")==0){
	         char *args[20];
                 int status;
                 int i=1;
                 char a[50];
                 while(tokens[i]!=NULL){ 
                   args[i]=tokens[i];
                   i++;
                   }
                chdir(tokens[1]); 
                printf("%s\n",getcwd(a,50));
                }             
                
	
       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);
             }  
	return 0;
}