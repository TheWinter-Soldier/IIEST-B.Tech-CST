#include <stdio.h>

int main() {
    int a[] = {2,5,7,19,26,33,56,61,70,89}, i, Element, Flag;
    printf("We have an array. Enter a key element to check if it's in the array: ");
    scanf("%d",&Element);
    
    Flag = 0;
    for(i=0;i<10;i++) {
        if(a[i] == Element) {
            Flag = 1;
            break;
        }
    }
    
    if(Flag==1) printf("Element found at index %d.\n",i);
    else printf("Not found.\n");
    
    return 0;
}