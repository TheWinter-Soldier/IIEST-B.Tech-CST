#include <stdio.h>

int main() {
    long long n;
    int i=1, Flag=0;
    printf("Enter any Integer to check if it's Perfect Number: ");
    scanf("%lld",&n);

    while(i<n) {
        if(n%i==0) Flag+=i;
        else Flag+=0;

        i++;
    }

    if(Flag==n) printf("%lld is a Perfect Number.\n",n);
    else printf("%lld is not a Perfect Number.\n",n);
    
    return 0;
}