//2017-EE-90
//Help taken from the chpater 3 of the book
//Pogram to implement shell in linux 
#include <stdio.h>
#include <sys/types.h> //Applicable in linux only
#include <sys/wait.h>  //The <sys/wait.h> header shall define the following symbolic constants for use with waitpid():
#include <unistd.h>
#include <string.h>

#define max_length 80 

int main(void){
  char *args[max_length/2 + 1]; // command line arguments 
  int exit = 1; //exit flag
  char user_input[max_length]; 
  int i = 0;
  
  int background = 0;//flag to update when process in background
  
  while(exit)
  {
    printf("OSH> ");
    fflush(stdout);
    scanf ("%[^\n]%*c", user_input);//take input from user

    i = 0;
    args[i] = strtok(user_input," ");
    while (args[i] != NULL)
    {
      i++;
      args[i] = strtok(NULL, " ");
    }

    if(strcmp(args[0], "exit") == 0) // exit command 
      break;

    if(strcmp(args[i-1], "&") == 0){ // & for background 
        printf("Run in background\n");
        args[i-1] = NULL;
        background = 1;
    } 

    pid_t pid; //process id
    pid = fork(); // fork creates child process
    if(pid < 0){  // pid of parent fork starts from 1 
        return 1;
    }
    
    if (pid == 0) //child fork
    {
        execvp(args[0],args); // exec() type command to change the address location of child process
        if (execvp(args[0],args) < 0) {     
           printf("ERROR: Invalid command\n");//if command is not valid 
           break;
        }
    }
    else if (!background) //waits for the child to complete execution
    {
        wait(NULL);
    }
  }
  return 0;
}





