#include <stdio.h>

int main(){
    long long n, Sum=0, Rev=0, d;
    printf("Enter any number: ");
    scanf("%lld",&n);

    while(n) {          //Here, only (n) and (n>0) are same
        d = n%10;
        n/=10;
        Sum+=d;
        Rev = (Rev*10)+d;
    }
    printf("\nThe sum of digits is = %lld and the reverse of the number is = %lld.\n",Sum,Rev);
    
    return 0;
}