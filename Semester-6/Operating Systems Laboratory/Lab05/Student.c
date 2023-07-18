#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  //for ftok(), shmat() and shmdt()
#include <sys/ipc.h>    //for shmget() and shmctl()
#include <sys/shm.h>    //for shmget(), shmat() and shmdt()

#include <time.h>       //for time(2)

#include <errno.h>      //for perror()

struct att {
    int roll;      //Roll-number
    time_t tm;     //To keep time of attendance
};

int main(int argc, char *argv[]) {
    int n,shmid;
    key_t MyKey;
    struct att *rolls;

    //check that at least one number is provided as command line argument
    if(argc<2) {
        printf("Error: at least one number must be provided as command line argument\n");
        return 1;
    }

    n = atoi(argv[1]);

    MyKey = ftok("/home/kuldip/Desktop/OS_Lab/Lab05",1);   //I got the key
    if(MyKey == -1) {
        perror("ftok() failed");
		exit(1);
	}

    shmid = shmget(MyKey,sizeof(rolls),0);
    if(shmid == -1) {             //shmget() failed()
        perror("shmget() failed: ");
        exit(2);
    }
    printf("shmget() returns shmid = %d.\n",shmid);

    rolls = shmat(shmid,NULL,0);
    if(rolls == (void *)-1) {     //shmat fails
        perror("shmat() failed: ");
        exit(4);
    }

    (rolls+(n-1))->roll = n;
    (rolls+(n-1))->tm = time(NULL);
    printf("My attendance has been given.\n");
    
    // detach shared memory
    if(shmdt(rolls) == 0) {
        printf("Shared memory successfully detached.\n");
    }
    else {
        perror("shmdt() failed: ");
    }

    return 0;
}