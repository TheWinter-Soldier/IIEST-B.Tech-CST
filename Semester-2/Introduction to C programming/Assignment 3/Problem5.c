#include <stdio.h>

int main() {
    int a, b;
    printf("Enter any bit: ");
    scanf("%d",&a);

    if(a==0) b=!a;
    else b=0;

    printf("NOT of what you entered = %d\n",b);

    return 0;
}