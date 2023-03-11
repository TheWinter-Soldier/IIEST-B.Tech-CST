#include <stdio.h> 
#include <math.h>

int main() {
   int L, U, i, j, x, Count = 0, Flag=0;
   double Sum = 0.0;
   printf("We want to show all Armstrong Numbrs in a given range.\n");

   printf("Enter lower limit: ");
   scanf("%d",&L);
   printf("Enter upper limit: ");
   scanf("%d",&U);
   
   for(i=L;i<U;++i) {
      j=i;
      Count=0;
      while(j) {
         j/=10;
         ++Count;
      }

      j=i;
      Sum=0;
      while(j) {
         x=j%10;
         Sum+=pow(x,Count);
         j/=10;
      }  
      
      if((int)Sum==i) {
         printf("%d ",i);
         Flag=1;
      }  
   }

   if(Flag==1) printf("is/are the Armstrong numbers between %d and %d.\n",L,U);
   else printf("There are no Armstrong Numbers in this interval.\n");

   return 0;
}