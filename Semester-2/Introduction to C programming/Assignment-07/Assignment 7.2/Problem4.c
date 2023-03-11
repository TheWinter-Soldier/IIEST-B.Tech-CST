#include <stdio.h>

int GCD(int a,int b) {
    if(b==0) return a;
    else return GCD(b,a%b);
}

int main() {
    int a, b;
    printf("Enter two numbers whose GCD you want to calculate: ");
    scanf("%d %d",&a,&b);

    printf("The GCD of %d and %d is %d.\n",a,b,GCD(a,b));
    
    return 0;
}