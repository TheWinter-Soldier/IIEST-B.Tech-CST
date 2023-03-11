#include <stdio.h> 

int main() {  
    int Row, i, j=0, Count=1; 
    printf("Enter the number of rows of the Floyd's Triangle to print: ");
    scanf("%d",&Row); 

    printf("The numerical stair is shown below: \n");
    for(i=1;i<=Row;i++) {
        while(j<i) {
            printf("%3d  ",Count++);

            j++;
        }
        printf("\n");
        
        j=0;
    }  
    
    return 0;
}