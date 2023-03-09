#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp; 
    int Line_c=0, Char_c=0; 
    char x, y;

    fp = fopen("File_for_Problem2.txt","r");
    if(fp==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }

    x = fgetc(fp);
    while(x != EOF) {
        if(x=='\n') {
            Line_c++;
        }

        x = fgetc(fp);
    }
    
    fseek(fp,0,SEEK_SET);

    y = fgetc(fp);
    while(y != EOF) {
        Char_c++;
        y = fgetc(fp);
    }

    printf("There are %d lines and %d Characters in the file.\n",Line_c+1,Char_c);

    fclose(fp);

    return 0;
}