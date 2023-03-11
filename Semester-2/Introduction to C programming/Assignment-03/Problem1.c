#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, s, area;
    printf("Enter the lengths of three sides of a tringle whose area you want to calculate: ");
    scanf("%lf %lf %lf",&a,&b,&c);

    s=(a+b+c)/2;
    area = sqrt(s*(s-a)*(s-b)*(s-c));

    printf("The area of the Triangle is = %.2lf\n",area);

    return 0;
}