#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
*
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


int main(int argc,char **argv[]) {
    
	int a = fork();
	
	if (a == 0) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	int s;
	int size;
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
		printf("Command entered: %s (remove this debug output later)\n", line);
		
		
		/* END: TAKING INPUT */
		
		
   		
   		

		//terminate with new line
		
		
		
		
		line[strlen(line)] = '\n';
		tokens = tokenize(line);
   
       //do whatever you want with the commands, here we just print them
		
		//for(i=0;tokens[i]!=NULL;i++){
		//	printf("found token %s (remove this debug output later)\n", tokens[i]);
       	//}
       	
		  
		 
       	
       	
       	
       	
       	if (tokens[0]==NULL){
       	
       	printf("No Input \n");
       	break;
       	}
       	
       	else{
       	
       	
       	
		execvp(tokens[0],tokens);
		
		}
		
		
		
		
		
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);
	
	
	
	}
	}
	
	else wait();
	
	return 0;
}
