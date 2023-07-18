#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  //for fork() and wait()
#include <unistd.h>     //for fork()
#include <sys/wait.h>   //for wait()

/*unction to compute the factorial of a number*/
unsigned long long fac(int n) {
    unsigned long long result = 1;
    for(int i=1;i<=n;i++) {
        result *= i;
    }
    
    return result;
}

int main(int argc,char *argv[]) {
    //check that at least one number is provided as command line argument
    if(argc<2) {
        printf("Error: at least one number must be provided as command line argument\n");
        return 1;
    }

    //create a child process for each number provided as command line argument
    for(int i=1;i<argc;i++) {
        int pid = fork();

        if(pid==0) {    //child process computes and prints the factorial of the number
            int n = atoi(argv[i]);
            printf("Factorial of %d is %llu.\n",n,fac(n));
            return 0;
        }
        else if(pid<0) {
            printf("Error: fork failed\n");
            return 1;
        }
    }

    //wait for all child processes to finish
    for(int i=1;i<argc;i++) {
        wait(NULL);
    }

    return 0;
}