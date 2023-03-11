#include <stdio.h>  

void Copy(char From_here[],char To_here[]) {  
    int i;

    for(i=0;i<100;i++) {
        To_here[i] = '\0';
    }
    for(i=0;From_here[i] != '\0';i++) {
        To_here[i] = From_here[i];
    }
    
    printf("The copied string is ---- %s\n",To_here);
}

int main() {  
   char str[100], destination[100];   
   printf("Enter the string: ");  
   gets(str);

   Copy(str,destination);

   return 0;
}