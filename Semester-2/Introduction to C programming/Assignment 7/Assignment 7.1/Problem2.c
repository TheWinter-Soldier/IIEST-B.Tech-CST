#include <stdio.h>

void Odd_Even(int a) {
    if(a%2 == 0) printf("%d is an Even number.\n",a);
    else printf("%d is an Odd number.\n",a);
}

int main() {
    int a;
    printf("Give an integer to check if it is even or odd: ");
    scanf("%d",&a);

    Odd_Even(a);
    
    return 0;
}