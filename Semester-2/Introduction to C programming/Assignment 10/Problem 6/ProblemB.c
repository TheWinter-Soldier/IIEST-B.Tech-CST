#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 128 
#define RSIZ 10 

int main() {
    FILE *fptr=NULL; 
    char line[RSIZ][LSIZ]; 
    int i=0, K=0;	

    fptr = fopen("Common_file.txt","r");

    while(fgets(line[i],LSIZ,fptr)) {
        line[i][strlen(line[i]) - 1] = '\0';

        i++;
    }
    K = i;

	printf("The contents of the file are:\n");    
    for(i=0;i<K;++i) {
        printf("%s\n",line[i]);
    }
    printf("The number of lines in the file are %d.\n",K);

    return 0;
}