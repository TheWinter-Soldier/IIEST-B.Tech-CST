#include <stdio.h>

#include <sys/types.h>  //for fork()
#include <unistd.h>     //for fork()

int main() {
    FILE *fp;
    char buffer[100];

    //Open the file for reading
    fp = fopen("Kuldip.txt","r");

    //Fork the process
    pid_t pid = fork();

    if(pid==0) {   //child process
        printf("Child process reading from file...\n");
        while(fgets(buffer,sizeof(buffer),fp) != NULL) {
            printf("Child: %s",buffer);
        }
    } 
    else {         //parent process
        printf("Parent process reading from file...\n");
        while(fgets(buffer,sizeof(buffer),fp) != NULL) {
            printf("Parent: %s",buffer);
        }
    }

    fclose(fp);
    return 0;
}