#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, x, y;
    printf("A general Quadratic Equation is of the form ax^2+bx+c = 0.\n");

    printf("Enter the co-efficients a, b and c respectively of such an equation: ");
    scanf("%lf %lf %lf",&a,&b,&c);

    if(((pow(b,2)) - (4*a*c)) < 0) printf("This equation does not have real roots.\n");
    else {
        x = (-b - sqrt((pow(b,2)) - (4*a*c)))/(2*a);
        y = (-b + sqrt((pow(b,2)) - (4*a*c)))/(2*a);

        if(x==y) printf("This equation has real and equal roots. The repeated root is %lf.\n",x);
        else printf("This equation has real and distinct roots. The roots are %lf and %lf.\n",x,y);
    }

    return 0;
}