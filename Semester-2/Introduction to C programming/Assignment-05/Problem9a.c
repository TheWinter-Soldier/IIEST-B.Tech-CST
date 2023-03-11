#include <stdio.h>
#include <math.h>

int main() {
    long n, S=0;
    int i=1;
    printf("Let's define a series S = 1-2+3-4+......upto n terms.\n");
    
    printf("Enter any Integer upto which S will be calculated: ");
    scanf("%ld",&n);

    while(i<=n) {
        S+=(pow((-1),(i-1)))*i;
        
        i++;
    }

    printf("S upto %ld terms is %ld.\n",n,S);
    
    return 0;
}