#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  //for fork(), wait(), shmat() and kill(2)
#include <unistd.h>     //for fork()
#include <sys/wait.h>   //for wait()
#include <sys/ipc.h>    //for shmget() and shmctl()
#include <sys/shm.h>    //for shmget(), shmctl() and shmat()

#include <signal.h>     //for signal() and kill(2)

#include <errno.h>      //for perror()

int shmid;              /* Stores the id of the shared memory segment as returned by shmget().
                           This variable is defined globally so that signal handler can access it for releasing the shared memory segment. */

typedef void (*sighandler_t)(int);
/* This is a signal handler for the keypress ^C, that is, ctrl-c. */
void releaseSHM(int signum) {
    int status;

    status = shmctl(shmid,IPC_RMID,NULL);   //IPC_RMID is the command for destroying the shared memory
    if(status==0) {
        fprintf(stderr,"\nRemoved shared memory with id = %d.\n",shmid);
    }
    else if(status == -1) {
        fprintf(stderr,"Cannot remove shared memory with id = %d.\n",shmid);
    } 
    else {
        fprintf(stderr,"shmctl() returned wrong value while removing shared memory with id = %d.\n",shmid);
    }

    status = kill(0,SIGKILL);
    if(status==0) {
        fprintf(stderr,"kill susccesful.\n");
    }
    else if(status == -1) {
        perror("kill failed.\n");
        fprintf(stderr,"Cannot remove shared memory with id = %d.\n",shmid);
    }
    else {
        fprintf(stderr,"kill(2) returned wrong value.\n");
    }
}

/* Function to calculate factorial of a number */
long long fac(int n) {
    int res=1;
    for(int i=1;i<=n;i++) {
        res *= i;
    }

    return res;
}

int main() {
    int status;
    pid_t pid=0, p1=0;
    sighandler_t shandler;
    
    shandler = signal(SIGINT,releaseSHM);   //Install signal handler     

    shmid = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0777);

    if(shmid == -1) {        //shmget() failed()
        perror("shmget() failed: ");
        exit(1);
    }

    printf("shmget() returns shmid = %d.\n",shmid);

    p1 = fork();
    if(p1==0) {         //child process
        long long x;
        int *pi_child;

        pi_child = shmat(shmid,NULL,0);
        if(pi_child == (void *)-1) {        //shmat fails
            perror("shmat() failed at child: ");
            exit(1);
        }

        while(1) {
            x = fac(*pi_child);
            printf("Child reads the number %d from shared memory and calculates factorial as %llu.\n",*pi_child,x);
            sleep(1);
        }

        exit(0);
    }
    else {              //parent process
        int *pi_parent;

        pi_parent = shmat(shmid,NULL,0);
        if(pi_parent == (void *)-1) {       //shmat fails
            perror("shmat() failed at parent: ");
            exit(1);
        }

        while(1) {
            *pi_parent = rand()%26;
            printf("Parent writes the number %d in shared memory.\n",*pi_parent);
            sleep(1);
        }
        
        pid = wait(&status);
        printf("pid = %d, status = %d!\n",pid,status);
        exit(0);
    }
}