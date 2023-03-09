#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, Min, Max, *A;
    printf("Enter the total number of elements: ");
    scanf("%d",&n);

    A = (int *)calloc(n,sizeof(int));
    
    for(i=0;i<n;i++) {
        printf("Enter the %d",i+1);
        if(i==0) printf("st ");
        else if(i==1) printf("nd ");
        else if(i==2) printf("rd ");
        else printf("th ");
        printf("number: ");
        scanf("%d",A+i);
    }

    Min = Max = *A;
    for(i=1;i<n;i++) {
        if(Min > *(A+i)) Min = *(A+i);
        if(Max < *(A+i)) Max = *(A+i);       
    }

    free(A);
    printf("The largest number is %d and the smallest is %d.\n",Max,Min);
    
    return 0;
}