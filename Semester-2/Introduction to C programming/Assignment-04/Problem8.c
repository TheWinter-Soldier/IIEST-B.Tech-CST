#include <stdio.h>
#include <math.h>

int main() {
    int x, a, b, c;
    printf("Here, we define a function:\nf(x) = 6x+1 when x>0,");
    printf("\n     = 2x^2 + 3 when 30 <= x <= 50,");
    printf("\n     = 5x^3 - 6 when 1 <= x <= 29,\n     = 0 otherwise.\n");
    printf("Note: f(x) is defined only on positive integers.\n");

    printf("For f(x) to be shown in output, enter an integer value of x: ");
    scanf("%d",&x);

    if(x>0) {
        a = 6*x + 1;
        if(x>=1 && x<=29) {
            b = 5*pow(x,3) - 6;
            printf("The function has two values at x=%d which are %d and %d.\n",x,a,b);
        }
        else if(x>=30 && x<=50) {
            c = 2*pow(x,2) + 3;
            printf("The function has two values at x=%d which are %d and %d.\n",x,a,c);
        }
        else printf("The value of f(x) at x=%d is %d.\n",x,a);
    }
    else printf("%d is out of the domain of definition of f(x).\n",x);

    return 0;
}