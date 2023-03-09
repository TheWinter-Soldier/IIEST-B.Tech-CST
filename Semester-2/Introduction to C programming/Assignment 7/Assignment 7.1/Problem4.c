#include <stdio.h>

int Minimum(int a[],int n,int i) {
    static int Min=0;

    if(i<n) {
        if(a[Min] > a[i]) {
            Min=i;   
		}
        Minimum(a,n,++i);
    }
	   
    return Min;
}

int Maximum(int a[],int n,int i) {
    static int Max=0;

    if(i<n) {
        if(a[Max] < a[i]) {
            Max=i;
		}
        Maximum(a,n,++i);
	}
    
    return Max;
}

int main() {
    int a[1000], i, n;
    printf("Enter the number of elements you want to analyse: ");
    scanf("%d",&n);
    
    printf("Enter the elements: ");
    for(i=0;i<n;i++) {
        scanf("%d",&a[i]);
    }
    
    printf("Minimum and Maximum among the given numbers are %d and %d respectively.\n",a[(Minimum(a,n,0))],a[(Maximum(a,n,0))]);

    return 0;
}