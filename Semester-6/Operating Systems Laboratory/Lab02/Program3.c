#include <stdio.h>

#include <sys/wait.h>   //for fork()
#include <unistd.h>     //for fork()


int main() {
    //open a file for writing
    FILE *fp = fopen("New.txt","w");
    if(fp == NULL) {
        perror("fopen");
        return 1;
    }

    int pid = fork();

    if(pid == 0) {           //child process: write to file
        fprintf(fp, "Hello from the child process!\n");
    } 
    else if(pid>0) {         //parent process: write to file
        wait(NULL);
        fprintf(fp, "Hello from the parent process!\n");

        //close the file
        fclose(fp);
    } 
    else {                   //error
        perror("fork");
        return 1;
    }

    return 0;
}