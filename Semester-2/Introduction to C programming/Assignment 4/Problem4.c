#include <stdio.h>

int main() {
    float x, y, z;
    printf("Enter 3 lenghts and we will check if they can form a Triangle: ");
    scanf("%f %f %f",&x,&y,&z);

    if(x+y<z) printf("These lenths cannot constitute a Triangle.\n");
    else if(y+z<x) printf("These lengths cannot constitute a Triangle\n");
    else if(z+x<y) printf("These lengths cannot constitute a Triangle\n");
    else printf("Congratulations! These lengths form a Triangle.\n");

    return 0;
}