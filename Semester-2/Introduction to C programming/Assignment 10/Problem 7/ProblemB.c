#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
	if(argc!=2) {
        printf("Please use \"./prg_name value1\" \n");
        printf("Here value 1 is the custom size of array.\n");
		return -1;
	}
    
    int a[50], n, i, sum=0;
    
    n = atoi(argv[1]);

    for(i=0;i<n;i++) {
        printf("Give ");
        if(i==0) printf("first ");
        else if(i==1) printf("second ");
        else if(i==2) printf("third ");
        else printf("%dth ",i+1);
        printf("element of array: ");
        scanf("%d",&a[i]);
    }

    for(i=0;i<n;i++) {
        sum += a[i];
    }

    printf("The sum of all elements in the array is %d.\n",sum);

    return 0;
}