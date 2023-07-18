/**
 * @file Student.c
 * @author Kuldip kundu (2020CSB022)
 * @brief Assignment 6 Question 2
 * @date 2023-02-07
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>        

#include <sys/types.h>  //for kill(2), ftok(), semget(), semop() and semctl()
#include <sys/ipc.h>    //for ftok(), semget(), semop() and semctl()
#include <sys/sem.h>    //for semget(), semop() and semctl()

#include <signal.h>     //for signal(2) and kill(2)

#include <errno.h>      //for perror()

#define SET_CARDINALITY	2
#define MAX_CHAIR 3

#define P(s,i) semop(s,(Pop+i),1);     //Does the decrement-operation
#define V(s,i) semop(s,(Vop+i),1);     //Does the increment-operation

const char *path = "/home/kuldip/Desktop/OS_Lab/Lab06";
int semid;         //The identifier of the Semaphore set

/* 
struct sembuf {
	unsigned short sem_num;   //semaphore number
	short          sem_op;    //semaphore operation
	short          sem_flg;   //operation flags
}
*/
struct sembuf *Pop;
struct sembuf *Vop;

union semun {
	int              val;    //Value for SETVAL
	struct semid_ds *buf;    //Buffer for IPC_STAT, IPC_SET
	unsigned short  *array;  //Array for GETALL, SETALL
	struct seminfo  *__buf;  //Buffer for IPC_INFO (Linux-specific)
} multiPurpose;

/**
 * @brief Get the semaphore of given idx from the semaphore set coressponding to the semid (global variable).
 *
 * @param idx 
 * @return int 
 */
int checkSem(int idx) {
    unsigned short int arr[SET_CARDINALITY];
	int status;
    multiPurpose.array = arr;

    status = semctl(semid,0,GETALL,multiPurpose);     //__semnum is ignored because of GETALL
    if(status == -1) {
        perror("semctl() failed: ");
        exit(1);
    }

    return arr[idx];
}

/**
 * @brief This is to check if the semaphore set is initialized or not. We ensure this by using an extra semaphore on the set with IPC_NOWAIT flag.
 * 
 * @return true
 * @return false
 */
bool isSetInitialized() {
    return checkSem(SET_CARDINALITY-1) != 0;     //This will be 0 iff no process has used it before
}

typedef void (*sighandler_t)(int);
/**
 * Following is a signal-handler for the keypress ^C, that is, ctrl-c.
 * This will free one chair and kill the process which was interrupted by pressing ^C.
 * Along with it, it decrements the last semaphore's value by 1 signifying that this process is no longer using it.
 * If the interrupted process was the only process using semaphores, then the Semaphore set is also removed.
 * 
 * @param signum
 */
void relSemaph(int signum) {
    int status;

    V(semid,0);                                  //One chair freed

	P(semid,SET_CARDINALITY-1);                  //Number of Process accessing set is reduced
    
	/*Will be removed if no other process is using the set.*/
	if(checkSem(SET_CARDINALITY-1) == 0) {
		status = semctl(semid,0,IPC_RMID);       //To remove set of Semaphores
		if(status==0) {
			fprintf(stderr,"Removed the Semaphore set with id = %d.\n",semid);
		}
		else if(status == -1) {
			fprintf(stderr,"Cannot remove the Semaphore set with id = %d.\n",semid);
		} 
		else {
			fprintf(stderr,"semctl() returned wrong value while removing the Semaphore set with id = %d.\n",semid);
		}
	}

    status = kill(0,SIGKILL);                    //To kill the process
    if(status==0) {
        fprintf(stderr,"kill susccesful.\n");
    }
    else if(status == -1) {
        perror("kill failed.\n");
    }
    else {
        fprintf(stderr,"kill(2) returned wrong value.\n");
    }
}

int main() {
	key_t mykey;
    
	//Installing the signal-handler
	sighandler_t shandler = signal(SIGINT,relSemaph);

    Pop = (struct sembuf *)malloc(SET_CARDINALITY*sizeof(struct sembuf));
    Vop = (struct sembuf *)malloc(SET_CARDINALITY*sizeof(struct sembuf));
    
    for(int i=0;i<SET_CARDINALITY;i++) {
		(Pop+i)->sem_num = i;
		(Pop+i)->sem_op = -1;

		(Vop+i)->sem_num = i;
		(Vop+i)->sem_op = 1;

		if(i != SET_CARDINALITY-1) {
			(Pop+i)->sem_flg = SEM_UNDO;
			(Vop+i)->sem_flg = SEM_UNDO;
		}
		else {
			(Pop+i)->sem_flg = IPC_NOWAIT;
			(Vop+i)->sem_flg = IPC_NOWAIT;
		}
    }

	mykey = ftok(path,1);
	if(mykey == -1) {
		perror("ftok() failed: ");
		exit(1);
	}

	semid = semget(mykey,SET_CARDINALITY,IPC_CREAT|0777);
	if(semid == -1) {
		perror("semget() failed: ");
		exit(2);
	}
    
	if(!isSetInitialized()) {
		printf("Semaphore set is not initialized. Initializing it:\n");
		for(int i=0;i < SET_CARDINALITY-1;i++) {
			multiPurpose.val = MAX_CHAIR;
			semctl(semid,i,SETVAL,multiPurpose);
		}
		printf("Semaphore set initialized.\n");
	}
	else {
		printf("Semaphore set is already initialized.\n");
	}
    
	V(semid,SET_CARDINALITY-1);

    P(semid,0);
    fprintf(stdout,"Please enter the classroom!\n");
	while(1) {
		getchar();
	}
    
    return 0;
}