#include<stdio.h> 

int main() {  
    int Row, i, j=0; 
    printf("Enter the number of rows to print: ");
    scanf("%d",&Row); 

    printf("\nThe reverse stair with stars is shown below:\n");
    for(i=Row;i>=0;i--) {
        while(j<i) {
            printf("* ");

            j++;
        }
        printf("\n");
        
        j=0;
    }  
    
    return 0;
}