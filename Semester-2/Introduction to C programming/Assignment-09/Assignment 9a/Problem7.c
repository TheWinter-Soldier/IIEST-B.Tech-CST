#include<stdio.h>
 
void swap(int *a,int *b) {
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;
}
 
int main() {
   int Num1, Num2;
 
   printf("Enter the first number: ");
   scanf("%d",&Num1);
   printf("Enter the Second number: ");
   scanf("%d",&Num2);
 
   swap(&Num1,&Num2);
 
   printf("After Swapping, First number: %d.\n",Num1);
   printf("After Swapping, Second number: %d.\n",Num2);

   return 0;
}