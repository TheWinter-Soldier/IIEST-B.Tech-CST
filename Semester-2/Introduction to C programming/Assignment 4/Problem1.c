#include <stdio.h>

int main() {
    double x, y, z, m, n;
    printf("Enter three numbers: ");
    scanf("%lf %lf %lf",&x,&y,&z);

    m = (x>y)*x + (x<y)*y;
    n = (m>z)*m + (m<z)*z;

    printf("The largest of the three given numbers is %lf.\n",n);

    return 0;
}