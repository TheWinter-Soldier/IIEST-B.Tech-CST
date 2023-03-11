#include <stdio.h>

int main() {
    long long Even, Odd, Sum; 
    double Average; 
    int a;
    printf("Here we will calculate the sum and average of two provided numbers, one of which would be even and the other would be odd.\n");

    printf("Enter any even number: ");
    while(1) {
        scanf("%lld",&Even);
        a = Even%2;
        if(a==0) break;
        else printf("You didn't provide an even number. Please provide....\n");
    }

    printf("Enter any odd number: ");
    while(1) {
        scanf("%lld",&Odd);
        a = Odd%2;
        if(a==1) break;
        else printf("You didn't provide an odd number. Please provide....\n");
    }

    Sum=Even+Odd;
    Average=Sum/2.0;

    printf("The sum of the provided numbers is %lld and their average is %lf.\n",Sum,Average);
    
    return 0;
}