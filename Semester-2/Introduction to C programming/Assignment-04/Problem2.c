#include <stdio.h>

int main() {
    long long a;
    printf("Enter any year: ");
    scanf("%lld",&a);

    if(a%100 == 0) {
        if(a%400 == 0) printf("%lld is a Leap year.\n",a);
        else printf("%lld is not a Leap year.\n",a); 
    } 
    else {
        if(a%4 == 0) printf("%lld is a Leap year.\n",a);
        else printf("%lld is not a Leap year.\n",a);
    }

    return 0;
}