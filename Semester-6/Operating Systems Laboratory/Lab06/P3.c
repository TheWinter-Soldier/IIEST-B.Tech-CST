/**
 * @file P3.c
 * @author Kuldip kundu (2020CSB022)
 * @brief Assignment 6 Question 1
 * @date 2023-02-07
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>        

#include <sys/types.h>  //for kill(2), ftok(), semget(), semop() and semctl()
#include <unistd.h>     //for sleep()
#include <sys/ipc.h>    //for ftok(), semget(), semop() and semctl()
#include <sys/sem.h>    //for semget(), semop() and semctl()

#include <signal.h>     //for signal(2) and kill(2)

#include <errno.h>      //for perror()

#define SET_CARDINALITY	5

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
 * Also, it has been used to terminate the process (cleverly, no shit, Einstein!).
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
 * It also removes the Semaphore set and terminates the process.
 * 
 * @param signum
 */
void relSemaph(int signum) {
    int status;

    status = semctl(semid,0,IPC_RMID);      //To remove set of Semaphores
    if(status==0) {
        fprintf(stderr,"Removed the Semaphore set with id = %d.\n",semid);
    }
    else if(status == -1) {
        fprintf(stderr,"Cannot remove the Semaphore set with id = %d.\n",semid);
    } 
    else {
        fprintf(stderr,"semctl() returned wrong value while removing the Semaphore set with id = %d.\n",semid);
    }

    status = kill(0,SIGKILL);               //To kill the process
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
	key_t myKey;
    
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

	myKey = ftok(path,1);
	if(myKey == -1) {
		perror("ftok() failed: ");
		exit(1);
	}

	semid = semget(myKey,SET_CARDINALITY,IPC_CREAT|0777);
	if(semid == -1) {
		perror("semget() failed: ");
		exit(2);
	}
    
	if(!isSetInitialized()) {
		printf("Semaphore set is not initialized. Initializing it:\n");
		for(int i=0;i < SET_CARDINALITY-1;i++) {
			if(i != 2) {
				multiPurpose.val = 0;
				semctl(semid,i,SETVAL,multiPurpose);
			}
			else {
				multiPurpose.val = 1;
				semctl(semid,i,SETVAL,multiPurpose);
			}
		}
        printf("Semaphore set initialized.\n");
	}
	else {
		printf("Semaphore set is already initialized.\n");
	}

	V(semid,SET_CARDINALITY-1);
    
    while(1) {
		checkSem(SET_CARDINALITY-1);
        P(semid,2);
        fprintf(stdout,"I am P3!\n");
        sleep(1);
		V(semid,3);
    }
    
    return 0;
}