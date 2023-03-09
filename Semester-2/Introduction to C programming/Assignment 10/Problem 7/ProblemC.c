#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	if(argc!=3) {
        printf("Please use \"./program_name string1 string2\"\n");
		return -1;
	}
    
    char A[100], B[100]; 
    int c;

    strcpy(A,argv[1]);
    strcpy(B,argv[2]);

    c = strcmp(A,B);

    if(c==0) printf("The strings are same.\n");
    else printf("The strings are not same.\n");
	
    return 0;
}