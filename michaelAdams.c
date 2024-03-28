/*
Name:Michael Adams

Course: COP4610
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int fact(int a) {
    //Calculate the factorial of a
    int factor = 1; 
    for (int i = 1 ; i <= a; i++) {
      factor = factor * i;
    }
   
    return printf("Child 1 (PID: %d) completed its task. Result: %d\n", getpid()+1, factor);
  
   
}

void multi(int b) {
    //Multiply b by itself
    b *= b;
    printf("Child 2 (PID: %d) completed its task. Result: %d\n", getpid()+2, b);
}

void customTask() {
    //Display text
    printf("Child 3 (PID: %d) completed its task. Result: Custom task completed\n\n", getpid()+3);
}


int main() {
   
    int n = 0; // Number of child processes
    int i = 0; //For loop 

    //Random Generated variables
    int a = rand() %4;
    int b = rand() %17;
    
    //Ask user for input
    printf("Enter the number of child :");
    scanf("%d", &n);

    // Get rid of the newline in input buffer
    getchar();

    
   //Declare fork after input to prevent double text syndrome
    pid_t pid = fork();
    for (int i = 0; i < n; i++){
        //If pid is less than 0, the fork either doesn't exist or failed
       if (pid < 0) {
        fprintf(stderr,"fork failed.\n");
        exit(1);
       
       //If pid is 0, children are executing processes
      } else if (pid == 0) {
         
         printf("Parent process (PID: %d) is creating %d child processes.\n\n", getpid(), n);
    
          // Child Process
          printf("Child %d (PID: %d) is computing the factorial of %d.\n", i+1, getpid()+1 , a);
          fact(a);

          printf("Child %d (PID: %d) is multiplying %d by %d.\n", i+2, getpid()+2,b, b);
          multi(b);
                  
          printf("Child %d (PID: %d) is performing a custom task.\n", i+3, getpid()+3); 
          customTask();
          
        //If pid is greater than 0, children are finished executing
      }else if( pid > 0) {
        //Parent Function 
        printf("All child processes have completed. Parent (PID: %d) is displaying the final message.", pid);
        //Parent will wait for Children to gather
        wait(NULL);
      }
      //Exit 
        exit(0);
        
    }
    return 0;
}
