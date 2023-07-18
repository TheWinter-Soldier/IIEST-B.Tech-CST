#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  //for fork() and waitpid()
#include <unistd.h>     //for fork() and execve()
#include <sys/wait.h>   //for waitpid()

#include <errno.h>      //for perror()

int main(int argc,char *argv[]) {
    int status;
    pid_t pid;
    char *exec_args[] = {NULL,NULL};

    if(argc<2) {
        printf("Usage: %s executable1 executable2 ... executableN\n", argv[0]);
        return 1;
    }

    for(int i=1;i<argc;i++) {
        pid = fork();
        if(pid<0) {
            perror("Fork failed");
            return 1;
        } 
        else if(pid==0) {    //Child process
            exec_args[0] = argv[i];
            if(execve(argv[i],exec_args,NULL) < 0) {
                perror("Exec failed");
            }
            exit(0);
        } 
        else {               // Parent process
            waitpid(pid,&status,0);
            if(WIFEXITED(status)) {
                printf("Child process %d terminated normally with exit status %d.\n\n",pid,WEXITSTATUS(status));
            } 
            else if(WIFSIGNALED(status)) {
                printf("Child process %d terminated abnormally due to signal %d.\n\n", pid,WTERMSIG(status));
            }
        }
    }

    return 0;
}
