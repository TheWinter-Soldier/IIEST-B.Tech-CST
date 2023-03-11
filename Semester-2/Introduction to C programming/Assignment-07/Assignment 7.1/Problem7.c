#include<stdio.h>

int main() {
    int Number, Sum=0, Count=0;
    printf("We will add 10 numbers for you, negative won't be added.\n");
    
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
        
        //Negative numbers are skipped
        if(Number>0) Sum += Number;    //Sum = Sum + number
    }
    
    //Display result
    printf("Sum = %d\n",Sum);
    
    return 0;
}