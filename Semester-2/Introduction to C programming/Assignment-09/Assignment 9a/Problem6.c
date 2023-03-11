#include<stdio.h>
#include<stdlib.h>

//-----------------Display Function-----------------
void Display(int Array[],int n) {
    for(int i=0;i<n;i++) printf("%d ",Array[i]);
}

//---------------------Bubble Sort Function-----------------------
void Bubble_sort(int Array[],int n) {
    int i, j, temp, *p;

    p = &Array[0];

    for(i=0;i<n;i++) {
        for(j=0;j<n-i-1;j++) {
            if(*(p+j) > *(p+j+1)) {
                temp = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = temp;
            }
        }
    }

    printf("After Bubble sort Elements are:\n[");
    Display(Array,n);
    printf("]\n");
}

int main() {
    int a[100], i, n;
    printf("This is a program to sort arrays.\n");

    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);
    printf("Enter the elements: ");
    for(i=0;i<n;i++) {
        scanf("%d",&a[i]);
    }

    Bubble_sort(a,n);
    
    return 0;
}