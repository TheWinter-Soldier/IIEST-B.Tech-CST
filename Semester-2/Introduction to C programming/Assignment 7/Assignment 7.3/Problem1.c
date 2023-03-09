#include <stdio.h>

int main() {
    int a[100], n, i, Element, Flag;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);
    printf("Enter the elements in the array:\n");
    for(i=0;i<n;i++) {
        scanf("%d",&a[i]);
    }

    printf("Enter a key element to check if it's in the array: ");
    scanf("%d",&Element);
    
    Flag=0;
    for(i=0;i<n;i++) {
        if(a[i] == Element) {
            Flag=1;
            break;
        }
    }
    
    if(Flag == 1) printf("Element found at array.\n");
    else printf("Not found.\n");
    
    return 0;
}