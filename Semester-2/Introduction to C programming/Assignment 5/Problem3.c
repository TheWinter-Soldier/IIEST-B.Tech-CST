#include <stdio.h>

int main() {
    long long a, b, Rev, x;
    printf("Enter any integer to verify if it's Palindrome: ");
    scanf("%lld",&a);
    b = a;
    Rev = 0;

    while(a) {
        x = a%10;
        a /= 10;
        Rev = (Rev*10)+x;
    }
    
    if(Rev==b) printf("%lld is a Palindrome Number.\n",b);
    else printf("%lld is not a Palindrome Number.\n",b);

    return 0;
}