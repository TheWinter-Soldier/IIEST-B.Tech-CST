#include <stdio.h>

int main() {
    int Array[50][50], T=0, i, j, x=1;
    for(i=0;i<5;i++)
    for(j=0;j<5;j++) {
        Array[i][j] = x++;
    }
    
    printf("There is a 5*5 Array. Enter competetion for each element to convert it into a Binary Array.\n");

    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            printf("Enter checker for a(%d,%d) : ",i,j);
            scanf("%d",&T);
            if(Array[i][j] >= T) Array[i][j] = 1;
            else Array[i][j] = 0;
            T=0;
        }
    }

    printf("The new look of the array is:\n");
    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            printf("%d  ",Array[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}