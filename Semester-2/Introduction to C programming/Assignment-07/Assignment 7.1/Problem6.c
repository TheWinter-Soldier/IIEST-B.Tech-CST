#include<stdio.h>

int main() {
    int Number, Sum=0, Count=0;
    printf("We will add a maximum of 10 numbers for you.\n");
    printf("Entering a negative number will terminate the acceptance and the result calculated till then will be produced.\n");
    
    for(int i=1 ; i<=10; i++) {
        Count++;

        //Take input from the user
        printf("Enter ");
        if(Count==1) printf("first ");
        else if(Count==2) printf("second ");
        else if(Count==3) printf("third ");
        else printf("%dth ",Count);
        printf("number: ");
        scanf("%d",&Number);
        
        //negative numbers are skipped
        if(Number<0) break; 
        
        Sum += Number;    //Sum = Sum + number
    }
    
    //Display result
    printf("Sum = %d\n",Sum);
   
    return 0;
}