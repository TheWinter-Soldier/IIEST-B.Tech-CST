#include<stdio.h>

int main() {
    int arr[10], i, *p;
    printf("Enter 10 numbers to populate the array: ");
    for(i=0;i<10;i++) scanf("%d",&arr[i]);

    p = &arr[0];

    for(i=5;i<10;i++) *(p+i) = *(p+i+1);

    printf("The final array after deleting 6th element is [");
    for(i=0;i<9;i++) printf("%d ",*(p+i));
    printf("].\n");

    return 0;
}