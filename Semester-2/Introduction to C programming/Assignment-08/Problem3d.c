#include <stdio.h>  

int compare(char a[],char b[]) {  
    int flag=0, i=0; 

    while(a[i] != '\0' &&b[i] != '\0') {  
       if(a[i] != b[i]) {  
           flag=1;  
           break;  
       } 

       i++;  
    } 

    if(flag==0) return 0;  
    else return (a[i]-b[i]);
} 

int main() {  
   char str1[20], str2[20]; 
   int c;

   printf("Enter the first string : ");  
   gets(str1);  
   printf("Enter the second string : ");  
   gets(str2);

   c = compare(str1,str2);    
   if(c==0) printf("Strings are same.\n");  
   else {
       printf("Strings are not same. ");
       printf("The first ASCII difference is %d.\n",c);
   }

   return 0;
} 