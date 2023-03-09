#include <stdio.h>

int main() {
    long long K;
    int i, n1=0, n2=1, n3;
    printf("Give an integer to print Fibonacci Sequence upto that many terms: ");
    scanf("%lld",&K);
    printf("The Fibonacci Sequence upto %lld terms is: ",K);

    for(i=0;i<K;i++) {
        n3 = n1+n2;
        if(i==0) printf("0 ");
        else if(i==1) printf("1 ");
        else printf("%lld ",n1);
        n1 = n2;
        n2 = n3;
    }

    printf("\n");

    return 0;
}