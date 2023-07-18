#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n;
    
    //check that at least one number is provided as command line argument
    if(argc<2) {
        printf("Error: at least one number must be provided as command line argument\n");
        return 1;
    }

    //create a child process for each number provided as command line argument
    for(int i=1;i<argc;i++) {
        n = atoi(argv[i]);
        printf("Square of %d is %d.\n",n,n*n);
    }
    
    return 0;
}