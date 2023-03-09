#include <stdio.h>

int Factorial(int n) {
   if(n==0) return 1;
   else return (n*(Factorial(n-1)));
}

int Combinatorial(int n,int r) {
   return (Factorial(n)/(Factorial(n-r)*Factorial(r)));
}

int main() {
   int Rows, i, j;
   printf("Enter the number of rows of the Pascal's Triangle is to be Printed: ");
   scanf("%d",&Rows);

   printf("\nThe Pascal's Triangle upto %d rows is:\n",Rows);
   for(i=0;i<Rows;i++) {
      for(j=0;j<=Rows-i;j++) {
         printf("  ");
      }
      for(j=0;j<=i;j++) {
         printf(" %3d",Combinatorial(i,j));
      }
      printf("\n");
   }
   
   return 0;
}