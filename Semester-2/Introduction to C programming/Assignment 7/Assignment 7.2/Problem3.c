#include <stdio.h>

int SumOfDigits(int num) {
    if(num==0) return 0;
    else return ((num%10) + SumOfDigits(num/10));
}

int main() {
    int num, Sum;
    printf("Enter any number to find sum of digits: ");
    scanf("%d",&num);
    
    Sum = SumOfDigits(num);
    
    printf("Sum of digits of %d is %d.\n",num,Sum);
    
    return 0;
}