#include<stdio.h> 

int main() {  
    int Row, i, j=0; 
    printf("Enter the number of rows you want to print: ");
    scanf("%d",&Row);

    printf("The numerical stair is shown below:\n");
    for(i=1;i <= Row;i++) {
        while(j<i) {
            if(j%2==0) printf("1  ");
            else printf("0  ");
            j++;
        }
        printf("\n");
        
        j=0;
    }  
    
    return 0;
}