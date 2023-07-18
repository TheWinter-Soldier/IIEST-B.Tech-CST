#include <stdio.h>
#include <stdlib.h>

//function to compute the factorial of a number
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for(int i=1;i<=n;i++) {
        result *= i;
    }
    
    return result;
}

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
        printf("Factorial of %d is %llu.\n",n,factorial(n));
    }
    
    return 0;
}