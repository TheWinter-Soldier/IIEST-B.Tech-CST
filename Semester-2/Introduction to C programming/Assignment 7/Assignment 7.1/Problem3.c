#include <stdio.h>

long long Factorial(int n) {
    if(n==0) return 1;
    else return (n*(Factorial(n-1)));
}

int Series(int n) {
    int Sum, i;

    Sum=0;
    for(i=1;i<=n;i++) {
        Sum+=((Factorial(i))/i);
    }
    
    return Sum;
}

int main() {
    int n;
    printf("Let's define a series like:\n\tS = (1!/1)+(2!/2)+(3!/3)+(4!/4)+.....\n");
    printf("Enter the number of terms upto which this series will be calculated: ");
    scanf("%d",&n);

    printf("S upto %d terms will be %d.\n",n,Series(n));
    
    return 0;
}