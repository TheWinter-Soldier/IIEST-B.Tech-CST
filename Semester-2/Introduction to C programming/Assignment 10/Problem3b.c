#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr1, *fptr2; 
    char x[200];

    fptr1 = fopen("File1_for_Problem3.txt","a");
    if(fptr1==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }
    fptr2 = fopen("File2_for_Problem3.txt","r");
    if(fptr2==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }

    fprintf(fptr1,"\n");
    while(fgets(x,200,fptr2)) {
        fprintf(fptr1,"%s",x);
    }

    fclose(fptr2);
    fclose(fptr1);

    return 0;
}