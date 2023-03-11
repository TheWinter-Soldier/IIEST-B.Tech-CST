#include <stdio.h>

int Fibonacci(int n) {
    if(n==0) return 0;
    else if(n==1) return 1;
    else return (Fibonacci(n-2)+Fibonacci(n-1));
}

int main() {
    int n, i=0;
    printf("Give an integer to print the Fibonacci sequence upto that many terms: ");
    scanf("%d",&n);

    printf("The Fibonacci Sequence upto %d terms is: ",n);
    while(i<n) {
        printf("%d  ",Fibonacci(i));
        i++;
    }

    return 0;
}