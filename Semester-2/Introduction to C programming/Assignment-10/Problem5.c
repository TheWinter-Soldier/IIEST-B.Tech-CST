#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp; 
    char x[50], y[5], z[20];

    fp = fopen("File_for_Problem5.txt","r");
    if(fp==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }

    fgets(x,50,fp);
    printf("\nName: %s",x);
    fgets(y,5,fp);   
    printf("Roll No.: %s",y);
    fgets(z,20,fp);
    printf("Percentage: %s\n",z);

    return 0;
}