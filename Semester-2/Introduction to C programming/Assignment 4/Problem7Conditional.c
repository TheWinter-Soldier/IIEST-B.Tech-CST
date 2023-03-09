#include <stdio.h>

int main() {
    double x, y, z, Temp;
    printf("Enter three numbers: ");
    scanf("%lf %lf %lf",&x,&y,&z);

    if(x>y) Temp=x;     //Using Conditional Statement
    else Temp=y;
    
    if(Temp>z) printf("The largest of the three given numbers is= %lf.\n",Temp);
    else printf("The largest of the three given numbers is= %lf.\n",z);

    return 0;
}