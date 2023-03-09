#include <stdio.h>
#include <math.h>

int main() {
    long long n;
    int i=2, flag=0;
    printf("Enter any Integer to check if it's Prime: ");
    scanf("%lld",&n);

    while(i < (int)sqrt((double)n)) {
        if(n%i==0) {
            flag=1;
            break; 
        } 
        
        i++;
    }

    if(flag==0) printf("%lld is a Prime Number.\n",n);
    else printf("%lld is not Prime.\n",n);
    
    return 0;
}