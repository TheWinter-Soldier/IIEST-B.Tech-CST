#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  //for fork(), wait(), shmat() and shmdt()
#include <unistd.h>     //for fork()
#include <sys/wait.h>   //for wait()
#include <sys/ipc.h>    //for shmget() and shmctl()
#include <sys/shm.h>    //for shmget(), shmctl(), shmat() and shmdt()

#include <errno.h>      //for perror()

#define N 3
#define M 5
#define P 4

int main() {
    int status,shmid,A[N][M],B[M][P];
    pid_t pid=0, px=0;
    int *C;

    //Read matrices A and B from user
    printf("Enter elements(row-wise fill) of the (%dx%d) matrix A:\n",N,M);
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%d",&A[i][j]);
        }
    }
    printf("Enter elements(row-wise fill) of the (%dx%d) matrix B:\n",M,P);
    for(int i=0;i<M;i++) {
        for(int j=0;j<P;j++) {
            scanf("%d",&B[i][j]);
        }
    }

    shmid = shmget(IPC_PRIVATE,(N*P)*sizeof(int),IPC_CREAT|0666);
    if(shmid == -1) {        //shmget() failed()
        perror("shmget() failed: ");
        exit(1);
    }
    printf("shmget() returns shmid = %d.\n",shmid);

    C = shmat(shmid,NULL,0);
    if(C == (void *)-1) {    //shmat fails
        perror("shmat() failed: ");
        exit(1);
    }
    
    //Create 1 child process for each row of final matrix
    for(int row=0;row<N;row++) {
        px = fork();
        if(px==0) {          //child process
            for(int i=0;i<P;i++) {
                C[(row*P) + i] = 0;
                for(int j=0;j<M;j++) {
                    C[(row*P) + i] += A[row][j]*B[j][i];
                }
            }
            exit(0);
        }
        else if(px<0) {    
            printf("Error creating child process for row %d.\n",row);
            exit(1);
        }
    }

    //Wait for all child-processes to finish
    for(int i=0;i<N;i++) {
        pid = wait(&status);
        printf("Child process with pid = %d terminated normally and exited with status = %d!\n",pid,status);
    }

    //Print the matrix C
    printf("The matrix C of size %dx%d is thus:\n",N,P);
    for(int i=0;i<N;i++) {
        for(int j=0;j<P;j++) {
            printf("%d\t",C[i*P+j]);
        }
        printf("\n");
    }

    //Detach and remove shared memory
    if(shmdt(C) == 0) {
        printf("Shared memory successfully detached.\n");
    }
    else {
        perror("shmdt() failed: ");
    }
    shmctl(shmid,IPC_RMID,NULL);
    if(status==0) {
        fprintf(stderr,"Removed shared memory with id = %d.\n",shmid);
    }
    else if(status == -1) {
        fprintf(stderr,"Cannot remove shared memory with id = %d.\n",shmid);
    } 
    else {
        fprintf(stderr,"shmctl() returned wrong value while removing shared memory with id = %d.\n",shmid);
    }

    return 0;
}