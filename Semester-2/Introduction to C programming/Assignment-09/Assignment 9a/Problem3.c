#include <stdio.h>

int main() {
   int a[10], Element, Flag=-1, i, *p;
   printf("Enter 10 elements to populate array a: ");
   for(i=0;i<10;i++) {
       scanf("%d",&a[i]);
   }

   p = &a[0];

   printf("Enter a key element to check if it's in the array: ");
   scanf("%d",&Element);

   for(i=0;i<10;i++) {
       if(*(p+i) == Element) {
           Flag = i;
           break;
       }
   }
   
   if(Flag == -1) printf("Element not found in the array.\n");
   else {
       printf("Element found at index %d.\n",Flag);
       printf("The adress of the key element is %p.\n",(p+Flag));
   }

   return 0;
}