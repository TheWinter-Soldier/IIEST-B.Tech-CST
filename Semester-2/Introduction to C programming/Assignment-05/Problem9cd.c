#include <stdio.h>
#include <math.h>

int main() {
    long n, S2=0; 
    double S1=0.0;
    int i=1;
    printf("Let's define two series\n");
    printf("\tS1 = (1/1)+(1/2)+(1/3)+(1/4)+......upto n terms.\n");
    printf("\tS2 = 1 +4 +9 +16 +......upto n terms.\n");

    printf("Enter any Integer upto which S1 and S2 will be calculated: ");
    scanf("%ld",&n);

    while(i<=n) {
        S1+=(1.0/i);

        i++;
    }

    i=1;
    while(i<=n) {
        S2+=(pow(i,2));
        
        i++;
    }

    printf("S1 upto %ld terms is %.4lf.\n",n,S1);
    printf("S2 upto %ld terms is %ld.\n",n,S2);
    
    return 0;
}