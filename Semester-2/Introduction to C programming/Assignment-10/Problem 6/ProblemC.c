#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp; 
    int Word_c=0, Char_c=0; 
    char x,y;

    fp = fopen("Common_file.txt","r");

    x = fgetc(fp);
    while(x != EOF) {
        if((x == ' ')||(x == '.')) {
            Word_c++;
        }
        x = fgetc(fp);
    }
    
    fseek(fp,0,SEEK_SET);

    y = fgetc(fp);
    while(y != EOF) {
        Char_c++;
        y = fgetc(fp);
    }

    printf("There are %d Words and %d Characters in the file.\n",Word_c,Char_c);

    fclose(fp);

    return 0;
}