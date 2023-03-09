#include <stdio.h>
#include <time.h>
#include <math.h>
 
int main() {
    long double time_spent = 0.0; 
    double a, b, x;

    clock_t begin = clock();

    a = pow((5000-1000),2);
    b = pow((10000-1000),2);
    x = (sqrt(a+b))/(5*2000);

    clock_t end = clock();
    time_spent += (long double)(end-begin)/CLOCKS_PER_SEC;

    printf("The elapsed time is %Lf seconds.\n",time_spent);
    printf("The value of the expression is %lf.\n",x);
    
    return 0;
}