#include <stdio.h>

int main() {
    int A[100], B[100], *p, *q, S[100], *r, n, i;

    printf("Here we add two custom arrays using pointers.\n");

    printf("Enter the number of elements in each array: ");
    scanf("%d",&n);

    printf("Enter elements to populate array A: ");
    for(i=0;i<n;i++) {
        scanf("%d",&A[i]);
    }
    printf("Enter elements to populate array B: ");
    for(i=0;i<n;i++) {
        scanf("%d",&B[i]);
    }

    p = &A[0];
    q = &B[0];
    r = &S[0];

    for(i=0;i<n;i++) {
        *(r+i) = *(p+i) + *(q+i);
    }

    printf("So, by adding successive elements of A and B, the new array is: \n");
    for(i=0;i<n;i++) printf("%d ",*(r+i));

    return 0;
}