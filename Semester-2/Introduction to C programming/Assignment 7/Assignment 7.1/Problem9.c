#include <stdio.h>

long long Factorial(int n) {
    if(n==0) return 1;
    else return (n*(Factorial(n-1)));
}

int main() {
    int a;
    printf("Enter the number whose factorial you want to calculate: ");
    scanf("%d",&a);

    printf("Factorial of %d is %lld.\n",a,Factorial(a));
    
    return 0;
}