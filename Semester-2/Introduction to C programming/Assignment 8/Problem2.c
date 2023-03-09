#include <stdio.h>
#include <string.h>

int main() {
  	char Sentence[200];
  	int i, j;

	printf("Enter any format-less sentence: ");
	gets(Sentence);
    
    for(i=0;Sentence[i] != '\0';i++) {
        if((Sentence[i] == Sentence[i+1]) && (Sentence[i]==' ')) {
            for(j=1;Sentence[i+j] != '\0';j++) {
                Sentence[i+j] = Sentence[i+1+j];
            }

            i-=1;
        }
        continue;
    }

    printf("Formatted sentence is:\n");
    printf("%s",Sentence);
	
    return 0;
}