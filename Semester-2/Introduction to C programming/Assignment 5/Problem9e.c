#include <stdio.h>
#include <math.h>

int main() {
    int n, i=1;  
    double S=0.0;
    printf("Let's define a series S = (1^1)+(3^2)+(5^3)+.....upto n terms.\n");

    printf("Enter any Integer upto which S will be calculated: ");
    scanf("%d",&n);

    while(i<=n) {
        S+=(pow(((2*i)-1),i));
        
        i++;
    }

    printf("S upto %d terms is %.0lf.\n",n,S);
    
    return 0;
}