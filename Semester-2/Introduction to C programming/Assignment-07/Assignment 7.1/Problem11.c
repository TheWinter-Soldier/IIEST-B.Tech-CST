#include <stdio.h>

int Factorial(int n) {
    if(n==0) return 1;
    else return (n*(Factorial(n-1)));
}

int Combinatorial(int n,int r) {
   return (Factorial(n) / (Factorial(n-r) * Factorial(r)));
}

void PascalsTriangleGenerator(int Rows) {
    int i, j;

    for(i=0;i<Rows;i++) {
        for(j=0;j<=Rows-i;j++) {
            printf("  ");
        }

        for(j=0;j<=i;j++) {
            printf(" %3d",Combinatorial(i,j));
        }

        printf("\n");
    }
}

int main() {
    int Rows;
    printf("Enter the number of rows of the Pascal's Triangle to be Printed: ");
    scanf("%d",&Rows);

    printf("The Pascal's Triangle upto %d rows is:\n",Rows);

    PascalsTriangleGenerator(Rows);

    return 0;
}