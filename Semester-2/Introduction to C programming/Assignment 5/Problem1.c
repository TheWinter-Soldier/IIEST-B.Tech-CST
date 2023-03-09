#include <stdio.h>
#include <math.h>

int main() {
    double x, n, y;
    printf("Here we will find the n-th power of a given Integer.\n");

    printf("Give the number: ");
    scanf("%lf",&x);
    printf("Give the power to which you want to raise it: ");
    scanf("%lf",&n);

    y = pow(x,n);

    printf("%lf raised to the power %.lf is %lf.\n",x,n,y);
    
    return 0;
}