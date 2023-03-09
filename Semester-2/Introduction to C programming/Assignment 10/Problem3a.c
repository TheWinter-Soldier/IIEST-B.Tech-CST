#include <stdio.h>
#include <stdlib.h> // For exit()

int main() {
    FILE *fptr1, *fptr2; 
    char c;

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
    c = fgetc(fptr2);
    while(c != EOF) {
        fputc(c,fptr1);
        c = fgetc(fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}