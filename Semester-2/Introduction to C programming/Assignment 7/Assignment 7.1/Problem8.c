#include <stdio.h>

void PrimeFactor(int Number) {
    int i, j, isPrime;

    printf("All Prime Factors of %d is/are:\n",Number); 
    for(i=2;i <= Number;i++) {
        if(Number%i==0) {
            isPrime = 1;
            for(j=2;j<=i/2;j++) {
                if(i%j==0) {
                    isPrime = 0;
                    break;
                }
            }

            if(isPrime==1) printf("%d ",i);
        }
    }
    printf(".\n");
}

int main() {
    int Number;
    printf("Enter any number to print Prime factors: ");
    scanf("%d",&Number);

    PrimeFactor(Number);

    return 0;
}