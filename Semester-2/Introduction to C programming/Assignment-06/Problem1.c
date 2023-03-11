#include <stdio.h> 
 
int main() {
    int a[1000], i, n, Min, Max, Sum;
    printf("Enter size of the array:\n");
    scanf("%d",&n);
 
    printf("Enter elements in array:\n");
    for(i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
 
    Min=Max=a[0];
    for(i=0; i<n; i++) {
        if(Min>a[i]) Min=a[i];
        if(Max<a[i]) Max=a[i];       
    }

    Sum=0;
    for(i=0;i<n;i++) {
        Sum+=a[i];
    }

    printf("Minimum of the array is %d and Maximum is %d.\n",Min,Max);
    printf("Sum of the array is %d.\n",Sum);
    
    return 0;
}