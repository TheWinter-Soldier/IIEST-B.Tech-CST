#include<stdio.h> 

int main() {  
    int num, row, col, space, count = 1; 
    printf("Enter the number of rows you want to print: ");
    scanf("%d",&num);

    printf("The numerical pyramid is shown below:\n");
    for(row=1;row <= num;row++) {
        for(space=1;space <= (num-row);space++) {
            printf("   "); 
        }  
        for(col=1;col <= ((2*row)-1);col++) {
            printf(" %2d", count++); 
        }    
        count = 1;
        printf("\n");  
    }  
    
    return 0;
}  