#include <stdio.h>

double Square(int a) {
    return a*a;
}

int main() {
    int n;
    printf("Enter the number whose square you want to know: ");
    scanf("%d",&n);
    
    printf("The square of %d is %.0lf.\n",n,Square(n));
    
    return 0;
}