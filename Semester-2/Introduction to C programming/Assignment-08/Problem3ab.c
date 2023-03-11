#include <stdio.h>
#include <string.h>

int Lencal(char String[]) {
    int i, Count=0;
    for(i=0;String[i] != '\0';i++) {
        Count++;
    }

    return Count;
}

void Reverse_string(char String[]) {
    int i; 
    char N[100];
    
    for(i=0;i<100;i++) {
        N[i] = '\0';
    }
    for(i=0;i<Lencal(String);i++) {
        N[Lencal(String)-i-1] = String[i];
    }

    printf("----- %s\n",N);
}

int main() {
  	char word[100];

	printf("Enter any string: ");
	gets(word);

	printf("The string has %d characters and its reverse is ",Lencal(word));
    Reverse_string(word);
    
    return 0;
}