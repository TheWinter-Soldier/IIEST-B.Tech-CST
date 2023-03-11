#include <stdio.h>

int PrimeChecker(long long n) {
    int flag=0,i=2;

    while(i<(n/2)) {
        if(n%i==0) {
            flag=1;
            break; 
        } 

        i++;
    }

    if(flag==0) return 1;
    else return 0;
}

int main() {
    long long n; 
    int x;
    printf("Enter any Integer to check if it's Prime: ");
    scanf("%lld",&n);

    x = PrimeChecker(n);

    if(x==1) printf("%lld is a Prime Number.\n",n);
    else printf("%lld is not Prime.\n",n);
    
    return 0;
}