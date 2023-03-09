#include <stdio.h> 
#include <stdlib.h>

int main() {  
    FILE *fp1, *fp2, *fp3; 
    char c;

    fp1 = fopen("File1_for_Problem4.txt","r");
    if(fp1==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }
    fp2 = fopen("File2_for_Problem4.txt","r");
    if(fp2==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }  
    fp3 = fopen("File3_For_Problem4.txt","a");
    if(fp3==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }
    
    c = fgetc(fp1);
    while(c != EOF) {
        fputc(c,fp3);
        c = fgetc(fp1);
    }
    fprintf(fp3,"\n");
    c = fgetc(fp2);
    while(c != EOF) {
        fputc(c,fp3);
        c = fgetc(fp2);
    } 
  
    printf("File1 and File2 have been merged into File3.\n"); 
  
    fclose(fp1); 
    fclose(fp2); 
    fclose(fp3);

    return 0;
}