#include <stdio.h>

int MaxFrequent(int Array[],int n) {
    int i, j, a, Max_Frequency=1, Mode=Array[0], Frequency_counter=1;
    
    for(i=0;i<n;++i) {
        for(j=i+1;j<n;++j) {
            if(Array[i] > Array[j]) {
                a = Array[i];
                Array[i] = Array[j];
                Array[j] = a;
            }
        }
    }
 
    for(i=1;i<n;i++) {
        for(j=0;j<i;j++) {
            if(Array[i] == Array[j]) Frequency_counter++;
            else Frequency_counter+=0;
            
            if(Frequency_counter > Max_Frequency) {
                Max_Frequency = Frequency_counter;
                Mode = Array[i];
            }
        }

        Frequency_counter = 1;
    }
 
    return Mode;
}

int main() {
    int A[50], i;
    printf("Let's define an array A with 10 elements.\n");
    printf("Enter the elements: ");
    for(i=0;i<10;i++) {
        scanf("%d",&A[i]);
    }

    printf("Element with maximum frequency is %d.\n",MaxFrequent(A,10));
    
    return 0;
}  