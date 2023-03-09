#include<stdio.h>

int main() {
    int arr[10], i, pos, Element;
    printf("Enter 9 numbers to populate the array: ");
    for(i=0;i<9;i++) scanf("%d",&arr[i]);

    printf("Enter the position where you want to replace an Element: ");
    scanf("%d",&pos);
    printf("Enter the Element which you wanna put: ");
    scanf("%d",&Element);

    for(i=9;i>pos;i--) arr[i] = arr[i-1];

    arr[pos] = Element;

    printf("Your final array is [");
    for(i=0;i<9;i++) printf("%d ",arr[i]);
    printf("].\n");

    return 0;
}