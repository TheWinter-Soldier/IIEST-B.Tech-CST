#include <stdio.h>

int main() {
    int arr[10], x, *p, i;
     
    p = &arr[0];
     
    printf("To populate the array of size 10:\n");
    for(i=0;i<10;i++) {
        printf("\t\tEnter ");
        if(i==0) printf("1st");
        else if(i==1) printf("2nd");
        else if(i==2) printf("3rd");
        else printf("%dth",i+1);
        printf(" element: ");
        scanf("%d",&arr[i]);
    }
    printf("The array you created is:\n");
    for(i=0;i<10;i++) {
        printf("%d ",*(p+i));
    }

    printf("\nEnter a replacement for the 6th element: ");
    scanf("%d",&x);
    *(p+5) = x;
     
    printf("The new array is:\n");
    for(i=0;i<10;i++) {
        printf("%d ",*(p+i));
    }
    
    return 0;
}