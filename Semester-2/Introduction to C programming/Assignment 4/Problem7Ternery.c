#include <stdio.h>

int main() {
    double x, y, z, Large;
    printf("Enter three numbers: ");
    scanf("%lf %lf %lf",&x,&y,&z);
                
    Large = (((x>y) ? x:y)>z) ? ((x>y) ? x:y):z; //Using Ternery Operators

    printf("The largest number is %lf.\n",Large);

    return 0;
}