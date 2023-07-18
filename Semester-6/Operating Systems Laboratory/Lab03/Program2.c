#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //for strncpy() 

#include <sys/types.h>  //for fork() and wait()
#include <unistd.h>     //for fork() and execve()
#include <sys/wait.h>   //for wait()

#include <errno.h>      //for perror()

#define MAX_ARGV 10     //for defining max size of argv in each passed executable

void forkAndExecute(char *filename,char *argv[]) {
    pid_t pid = fork();
    int status;
    if(pid<0) {
        perror("Fork failed");
    }
    else if(pid==0) {
        status = execve(filename,argv,NULL);
        if(status==-1) perror("execve failed");
        exit(0);
    }
    else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    int argvParser = 1,countArgToLoad = 1;
    char *execLoader[MAX_ARGV];

    if(argc < 2) {
        printf("Usage: %s executable1.out -arg1 -arg2 ... -argI executable2.out -arg1 -arg2 ... -argJ ... executableN.out -arg1 -arg2 ... -argK\n",argv[0]);
        return 1;
    }

    while(argvParser<argc) {
        execLoader[0] = argv[argvParser];
        countArgToLoad = 1;
        argvParser++;

        while(argvParser<argc && countArgToLoad<MAX_ARGV && argv[argvParser][0]=='-') {
            //execLoader[countArgToLoad] = argv[argvParser];
            execLoader[countArgToLoad] = malloc(sizeof(char)*(strlen(argv[argvParser])-1));
            strncpy(execLoader[countArgToLoad],argv[argvParser]+1,strlen(argv[argvParser])-1);
            argvParser++;
            countArgToLoad++;
        }

        execLoader[countArgToLoad] = NULL;
        forkAndExecute(execLoader[0],execLoader);
    }
    
    return 0;
}