#include <stdio.h>

int main() {
    long long a, b;
    printf("Enter first number: ");
    scanf("%lld",&a);
    printf("Enter second number: ");
    scanf("%lld",&b);

    a = a-b;
    b = a+b;
    a = b-a;

    printf("After swapping first number is %lld and second number is %lld.\n",a,b);
    
    return 0;
}