#include<stdio.h>
#include<stdlib.h>

//-------------------Display Function-----------------
void Display(int Array[],int n) {
    printf("[");
    for(int i=0;i<n;i++) printf("%d ",Array[i]);
    printf("]\n");
}

//--------------Bubble Sort Function----------------
void Bubble_sort(int Array[],int n) {
    int i, j, temp;

    for(i=0;i<n;i++) {
        for(j=0;j<n-i-1;j++) {
            if(Array[j] > Array[j+1]) {
                temp = Array[j];
                Array[j] = Array[j+1];
                Array[j+1] = temp;
            }
        }
    }

    printf("After Bubble sort Elements are:\n");
    Display(Array,n);
}

//------------------Selection Sort Function------------------
void Selection_sort(int Array[],int n) {
    int i, j, temp;
    
    for(i=0;i<n-1;i++) {
        for(j=i+1;j<n;j++) {
            if(Array[i] > Array[j]) {
                temp = Array[i];
                Array[i] = Array[j];
                Array[j] = temp;
            }
        }

    }

    printf("After Selection sort Elements are:\n");
    Display(Array,n);
}

//-----------------Insertion Sort Function-------------------
void Insertion_sort(int Array[],int n) {
    int i, j, min;

    for(i=1;i<n;i++) {
        min = Array[i];
        j=i-1;
        while((min < Array[j]) && (j>=0)) {
            Array[j+1] = Array[j];
            j=j-1;
        }
        Array[j+1] = min;
    }
    
    printf("After Insertion sort Elements are:\n");
    Display(Array,n);
}

int main() {
    int n, Choice, i, Array[100], Count=0;
    printf("Enter no. of elements you want to sort: ");
    scanf("%d",&n);
    printf("Enter the elements: ");
    for(i=0;i<n;i++) {
        scanf("%d",&Array[i]);
    }
    
    printf("Please select any option Given Below for Sorting:\n");
    while(1) {
        Count++;
        printf("\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Display Array.\n5. Exit the Program.\n");
        printf("\nEnter your Choice");
        if(Count>1) printf(" again");
        printf(": ");
        scanf("%d",&Choice);
        
        switch(Choice) {
            case 1:
            Bubble_sort(Array,n);
            break;
            
            case 2:
            Selection_sort(Array,n);
            break;
            
            case 3:
            Insertion_sort(Array,n);
            break;
            
            case 4:
            Display(Array,n);
            break;
            
            case 5:
            printf("Program terminated successfully.\n");
            return 0;
            
            default:
            printf("Please Select 1-5 option only ----\n");
        }
    }

    return 0;
}