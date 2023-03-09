#include <stdio.h>

int BinarySearch(int Array[],int Low_index,int End_index,int x) {
    int i, y, j, Flag=0;

    for(i=0;i < End_index+1;++i) {
        for(j=i+1;j < End_index+1;++j) {
            if(Array[i] > Array[j]) {
                y =  Array[i];
                Array[i] = Array[j];
                Array[j] = y;
            }
        }
    }

    while(End_index >= Low_index) {
        int Mid = (End_index+Low_index)/2;

        if(Array[Mid] == x) {
            Flag=0;
            return Mid;
        }
        else if(Array[Mid] > x) End_index = Mid-1;
        else Low_index = Mid+1;
    }

    if(Flag==0) return -1;

    return 0;
}

int main() {
    int a[100], i, Element, n, Z;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);
    printf("Enter the elements: ");
    for(i=0;i<n;i++) {
        scanf("%d",&a[i]);
    }

    printf("Enter a key element to check if its in the array: ");
    scanf("%d",&Element);

    Z = BinarySearch(a,0,n-1,Element);

    if(Z == -1) printf("Element not found in the array.\n");
    else printf("Element belongs to the array.\n");
    
    return 0;
}