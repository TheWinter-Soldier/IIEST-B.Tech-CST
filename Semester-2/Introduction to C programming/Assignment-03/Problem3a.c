#include <stdio.h>

int main() {
    long long First, Second, Temporary;
    printf("Enter first number: ");
    scanf("%lld",&First);
    printf("Enter second number: ");
    scanf("%lld",&Second);

    Temporary = First;
    First = Second;
    Second = Temporary;

    printf("After swapping first number is %lld and second number is %lld.\n",First,Second);
    
    return 0;
}