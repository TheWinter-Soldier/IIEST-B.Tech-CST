#include <stdio.h>

int main() {
    int arr[10], *p, i;
     
    p = &arr[0];

    printf("Fill an array of size 10 and see address of elements.\n");
     
    printf("To populate the array:\n");
    for(i=0;i<10;i++) {
        printf("\t\tEnter ");
        if(i==0) printf("1st");
        else if(i==1) printf("2nd");
        else if(i==2) printf("3rd");
        else printf("%dth",i+1);
        printf(" element: ");
        scanf("%d",&arr[i]);
    }
     
    printf("Entered array elements are:\n");
    printf("Address\t\tValue\n");
    printf("--------\t------\n");
    for(i=0;i<10;i++) {
        printf("%p\t  %d\n",(p+i),arr[i]);
    }
    
    return 0;
}