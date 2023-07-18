/**
 * @file Q1.c
 * @author Kuldip Kundu (2020CSss022)
 * @brief Assignment 7 Question 1
 * @date 2023-02-14
 */
#include <stdio.h>
#include <stdlib.h>          //for _exit()
#include <string.h>          //for memset()

#include <unistd.h>          //for fork(), exit(), read(), write() and close()
#include <sys/wait.h>        //for wait()
#include <sys/types.h>       //for fork() and wait()

#include <errno.h>           //for perror()

#define READ_END 0
#define WRITE_END 1

struct student {
    int roll;           //Roll numsser
    char name[100];     //Name of student
};

/**
 * @brief This is a satellite function called by the mergeSort function.
 * It helps to merge the sub-arrays of a.
 * 
 * @param a (struct student *)
 * @param start (int)
 * @param mid (int)
 * @param end (int)
 */  
void merge(struct student *a,int start,int mid,int end) {
    int p, q, r, n1, n2;

    n1 = mid - start + 1;
    n2 = end - mid;

    struct student *LeftArray = (struct student *)malloc(n1*sizeof(struct student));
    struct student *RightArray = (struct student *)malloc(n2*sizeof(struct student));     
      
    //copy data to temporary arrays
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
        if((LeftArray+p)->roll <= (RightArray+q)->roll) {
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

/**
 * @brief This is a function to implement Merge sort.
 * 
 * @param a (struct student *)
 * @param lIndex (int)
 * @param rIndex (int)
 */
void mergeSort(struct student *a,int lIndex,int rIndex) {
    if(lIndex < rIndex) {
		int m = lIndex + (rIndex - lIndex)/2;

		//Sort first and second halves
		mergeSort(a,lIndex,m);
		mergeSort(a,m+1,rIndex);

		merge(a,lIndex,m,rIndex);
	}
}

int main(int argc,char *argv[]) {
	if(argc<2) {
		fprintf(stdout,"Give one command-line argument.\n");
        return 1;
	}

    int n, PtoCfd[2], CtoPfd[2], flag;
    pid_t cpid;

    n = atoi(argv[1]);
    if(n>100) {
		fprintf(stdout,"Argument should be less than 100.\n");
        return 1;
	}

    flag = pipe(PtoCfd);          //Pipe dedicated for data transfer from parent to child
	if(flag == -1) {
		perror("pipe() failed");
		exit(EXIT_FAILURE);
	}
    flag = pipe(CtoPfd);          //Pipe dedicated for data transfer from child to parent
	if(flag == -1) {
		perror("pipe() failed");
		exit(EXIT_FAILURE);
	}

    cpid = fork();
    if(cpid == -1) {
        perror("fork() failed");
        exit(EXIT_FAILURE);
    }
    else if(cpid==0) {                                          //Child Process
        close(PtoCfd[WRITE_END]); //Child will not use this pipe to write
        close(CtoPfd[READ_END]);  //Child will not read from this pipe

        struct student recvData[100];
        memset(&recvData,0,100*sizeof(struct student));
        
        if(read(PtoCfd[READ_END],&recvData,n*sizeof(struct student)) < 0) {
            perror("Reading from parent failed");
            _exit(EXIT_FAILURE);
        }
        close(PtoCfd[READ_END]);

        mergeSort(&recvData[0],0,99);

        if(write(CtoPfd[WRITE_END],&recvData,100*sizeof(struct student)) < 0) {
            perror("writing from child to parent failed");
            _exit(EXIT_FAILURE);
        }
        close(CtoPfd[WRITE_END]);

        _exit(EXIT_SUCCESS);
    }
    else {                                                      //Parent process
        close(CtoPfd[WRITE_END]); //Parent will not use this pipe to write
        close(PtoCfd[READ_END]);  //Parent will not read from this pipe

        struct student ss[100];
        memset(&ss,0,100*sizeof(struct student));
        
        //Taking data of students from user
        for(int i=0;i<n;i++) {
            printf("Give Roll-number and Name of %d",i+1);
            if((i%10) == 0) {
                printf("st student ---\n");
            }
            else if((i%10) == 1) {
                printf("nd student ---\n");
            }
            else if((i%10) == 2) {
                printf("rd student ---\n");
            }
            else {
                printf("th student ---\n");
            }
            printf("Roll: ");
            scanf("%d",&(ss[i].roll));
            printf("Name of Student: ");
            scanf("%s",ss[i].name);
        }

        if(write(PtoCfd[WRITE_END],&ss,n*sizeof(struct student)) < 0) {
            perror("writing from parent to child failed");
            exit(EXIT_FAILURE);
        }
        close(PtoCfd[WRITE_END]);
        
        if(read(CtoPfd[READ_END],&ss,100*sizeof(struct student)) < 0) {
            perror("Retrieving sorted array from child failed");
            exit(EXIT_FAILURE);
        }
        close(CtoPfd[READ_END]);

        printf("The record of students are -----\n");
        printf("Roll\t\tName\n");
        for(int j=100-n;j<100;j++) {
            printf("%d\t\t%s\n",ss[j].roll,ss[j].name);
        }

        wait(NULL);

        exit(EXIT_SUCCESS);
    }

    return 0;
}