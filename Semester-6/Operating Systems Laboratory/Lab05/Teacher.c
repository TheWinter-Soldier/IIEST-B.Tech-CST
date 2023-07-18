#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  //for ftok(), shmat() and kill(2)
#include <unistd.h>     //for sleep()
#include <sys/ipc.h>    //for shmget() and shmctl()
#include <sys/shm.h>    //for shmget(), shmctl() and shmat()

#include <signal.h>     //for signal() and kill(2)

#include <time.h>       //for time(2) and ctime()

#include <errno.h>      //for perror()

struct att {
    int roll;      //Roll-number
    time_t tm;     //To keep time of attendance
};

int n,shmid;
struct att *rolls;

/* Function to merge the subarrays of a[] */  
void merge(struct att *a,int start,int mid,int end) {
    int p,q,r,n1,n2;

    n1 = mid - start + 1;
    n2 = end - mid;

    struct att *LeftArray = (struct att *)malloc(n1*sizeof(struct att));
    struct att *RightArray = (struct att *)malloc(n2*sizeof(struct att));     
      
    /* copy data to temp arrays */  
    for(int i=0;i<n1;i++) {
        *(LeftArray+i) = *(a+start+i);
    } 
    for(int j=0;j<n2;j++) {
        *(RightArray+j) = *(a+mid+1+j);
    }

    p = 0,         //initial index of first sub-array 
    q = 0;         //initial index of second sub-array 
    r = start;     //initial index of merged sub-array 
      
    while((p<n1) && (q<n2)) {
        if((LeftArray+p)->tm <= (RightArray+q)->tm) {
            *(a+r) = *(LeftArray+p);    
            p++;    
        }    
        else {    
            *(a+r) = *(RightArray+q);    
            q++;    
        }    
        r++;    
    }

    while(p<n1) {
        *(a+r) = *(LeftArray+p);    
        p++;    
        r++;    
    }

    while(q<n2) {
        *(a+r) = *(RightArray+q);    
        q++;    
        r++;    
    }    
}

/* Function to implement Merge-sort */
void mergeSort(struct att *a,int lIndex,int rIndex) {
    if(lIndex < rIndex) {
		int m = lIndex + (rIndex - lIndex)/2;

		//Sort first and second halves
		mergeSort(a,lIndex,m);
		mergeSort(a,m+1,rIndex);

		merge(a,lIndex,m,rIndex);
	}
}

typedef void (*sighandler_t)(int);
/* This is a signal handler for the keypress ^C, that is, ctrl-c. */
void releaseSHM(int signum) {
    int status;
    
    //Sort the array and print the attendance data
    mergeSort(rolls,0,n-1);
    for(int i=0;i<n;i++) {
        if((rolls+i)->roll != -1) {
            printf("Roll no. %d marked his/her attendance on %s.",(rolls+i)->roll,ctime(&(rolls+i)->tm));
        }
    }

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
        fprintf(stderr,"Kill susccesful.\n");    
    }
    else if(status == -1) {
        perror("Kill failed.\n");
        fprintf(stderr,"Cannot remove shared memory with id = %d.\n",shmid);
    }
    else {
        fprintf(stderr,"kill() returned wrong value.\n");
    }
}

int main(int argc,char *argv[]) {
    key_t MyKey;
    sighandler_t shandler;

    shandler = signal(SIGINT,releaseSHM);   //Install signal handler

    //check that at least one number is provided as command line argument
    if(argc<2) {
        printf("Error: at least one number must be provided as command line argument\n");
        return 1;
    }

    n = atoi(argv[1]);

    MyKey = ftok("/home/kuldip/Desktop/OS_Lab/Lab05",1);   //I created a key
    if(MyKey == -1) {
        perror("ftok() failed");
		exit(1);
	}

    shmid = shmget(MyKey,n*sizeof(struct att),IPC_CREAT|0666);
    if(shmid == -1) {             //shmget() failed()
        perror("shmget() failed: ");
        exit(2);
    }
    printf("shmget() returns shmid = %d.\n",shmid);

    rolls = shmat(shmid,NULL,0);
    if(rolls == (void *)-1) {    //shmat fails
        perror("shmat() failed: ");
        exit(4);
    }
    printf("Shared Memory successfully attached.\n");

    for(int i=0;i<n;i++) {
        (rolls+i)->roll = -1;
        (rolls+i)->tm = (time_t)0;
    }
    
    printf("Mark your attendance for the next 200 seconds.\n");
    sleep(200);

    return 0;
}