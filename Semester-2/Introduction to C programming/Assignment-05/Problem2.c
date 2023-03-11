#include <stdio.h>

int main() {
    long long a, Sum, x;
    printf("Enter any integer and we will show its sum of digits: ");
    scanf("%lld",&a);
    
    Sum = 0;
    while(a) {
        x = a%10;
        a = a/10;
        Sum+=x;
    }
    
    printf("Sum of the digits is %lld.\n",Sum);
    
    return 0;
}