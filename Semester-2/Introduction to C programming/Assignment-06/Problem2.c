#include <stdio.h> 
 
int main() {
    int a[1000], b[1000], c[1000], i;
    printf("A and B are two arrays with 10 elements each.\n");
    printf("C is defined as C[i]= A[i]+B[10-i], where i=0(1)9.\n");
 
    printf("Enter elements in array A: ");
    for(i=0;i<10;i++) {
        scanf("%d",&a[i]);
    }
    printf("Enter elements in array B: ");
    for(i=0;i<10;i++) {
        scanf("%d",&b[i]);
    }

    for(i=0;i<10;i++) {
        c[i] = a[i]+b[9-i];
    }

    printf("The array C is:\n");
    for(i=0;i<10;i++) {
        printf("%d ",c[i]);
    }

    return 0;
}