#include <stdio.h>

int main() {
    int a,b,c;
    printf("Give first number: ");
    scanf("%d",&a);
    printf("Give second number: ");
    scanf("%d",&b);
    
    c = a * b;
    
    printf("The product of %d and %d is %d.\n",a,b,c);
}
