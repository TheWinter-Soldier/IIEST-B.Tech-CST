#include <stdio.h>

int main() {
    float t, c;
    printf("Enter the Temperature in Fahrenheit: ");
    scanf("%f",&t);

    c = 5*((t-32)/9);

    printf("In Celsius scale the Temperature is = %.2lf\n",c);

    return 0;
}