#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
	if(argc!=3) {
        printf("Please use \"./program_name value1 value2\"\n");
		return -1;
	}

	int a, b, sum;
	
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	sum = a+b;
	
	printf("Sum of %d and %d is %d.\n",a,b,sum);
	
    return 0;
}