#include<stdio.h>
#include<unistd.h>  

int main() {
    char s[100];
    printf("Your current working directory is %s\n",getcwd(s,100));

    return 0;
}