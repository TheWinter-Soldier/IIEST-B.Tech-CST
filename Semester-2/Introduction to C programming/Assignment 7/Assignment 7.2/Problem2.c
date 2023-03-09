#include <stdio.h>

long long Factorial(int n) {
    if(n==0) return 1;
    else return (n*(Factorial(n-1)));
}

int main() {
    int n, i=0;
    printf("Enter any integer to find its factorial: ");
    scanf("%d",&n);

    printf("The factorial of %d is %lld.\n",n,Factorial(n));

    return 0;
}