#include <stdio.h>

void Transpose() {
    int Array[100][100], Transpose[10][10], r, c, i, j;
    printf("Enter rows and columns: ");
    scanf("%d %d",&r,&c);
    printf("Enter matrix elements:\n");
    for(i=0;i<r;++i) {
        for(j=0;j<c;++j) {
            printf("Enter element a(%d,%d): ",i+1,j+1);
            scanf("%d",&Array[i][j]);
        }
    }
    
    printf("Entered matrix:\n");
    for(i=0;i<r;++i) {
        for(j=0;j<c;++j) {
            printf("%d  ",Array[i][j]);
            if(j == c-1) printf("\n");
        }
    }
    
    for(i=0;i<r;++i) {
        for(j=0;j<c;++j) {
            Transpose[j][i] = Array[i][j];
        }
    }

    printf("Transpose of the matrix:\n");
    for(i=0;i<c;++i) {
        for(j=0;j<r;++j) {
            printf("%d  ",Transpose[i][j]);
            if(j == r-1) printf("\n");
        }
    }
}
 
void MatrixAddition() {
    int r, c, i, j, First[100][100], Second[100][100], Sum[100][100];
    printf("Enter the number of rows and columns of matrix: ");
    scanf("%d %d",&r,&c);

    printf("For the First matrix -----\n");
    for(i=0;i<r;++i) {
        for(j=0;j<c;++j) {
            printf("Enter element a(%d,%d): ",i+1,j+1);
            scanf("%d",&First[i][j]);
        }
    }
    printf("\n");

    printf("For the Second matrix -----\n");
    for(i=0;i<r;++i) {
        for(j=0;j<c;++j) {
            printf("Enter element b(%d,%d): ",i+1,j+1);
            scanf("%d",&Second[i][j]);
        }
    }
    printf("\n");

    for(i=0;i<r;++i) {
        for(j=0;j<c;++j) {
            Sum[i][j] = 0;
        }
    }

    printf("Sum of entered matrices:\n");
    for(i=0;i<r;i++) {
        for(j=0;j<c;j++) {
            Sum[i][j] = First[i][j] + Second[i][j];
            printf("%d\t",Sum[i][j]);
        }
        printf("\n");
    }
}
 
void MatrixMultiplication() {
    int r, c, N, i, j, n, First[100][100], Second[100][100], Product[100][100];
    
    printf("For the First matrix -----\n");
    printf("Enter the number of rows and columns: ");
    scanf("%d %d",&r,&N);
    for(i=0;i<r;++i) {
        for(n=0;n<N;++n) {
            printf("Enter element a(%d,%d): ",i+1,n+1);
            scanf("%d",&First[i][n]);
        }
    }
    printf("\n");

    printf("For the Second matrix -----\n");
    printf("The number of rows should be %d. Enter the number of columns: ",N);
    scanf("%d",&c);
    for(n=0;n<N;++n) {
        for(j=0;j<c;++j) {
            printf("Enter element b(%d,%d): ",n+1,j+1);
            scanf("%d",&Second[n][j]);
        }
    }
    printf("\n");

    for(i=0;i<r;++i) {
        for(j=0;j<c;++j) {
            Product[i][j] = 0;
        }
    }
    printf("The product matrix is:\n");
    for(i=0;i<r;i++) {
        for(j=0;j<c;j++) {
            for(n=0;n<N;n++) {
                Product[i][j] += (First[i][n] * Second[n][j]);
            }
            printf("%d\t",Product[i][j]);
        }
        printf("\n");   
    }
}

int main() {
    int Choice, Count=0;
    printf("This is a menu driven program for Matrix-operations.\n");
    
    while(1) {
        Count++;
        printf("\n1. Find Transpose of a Matrix.\n2. Add two Matrices.\n3. Multiply two Matrices.\n4. Exit the Program.\n");
        printf("\nEnter your Choice");
        if(Count>1) printf(" again");
        printf(": ");
        scanf("%d",&Choice);

        switch(Choice) {
            case 1:
            Transpose();
            break;
            
            case 2:
            MatrixAddition();
            break;
            
            case 3:
            MatrixMultiplication();
            break;

            case 4:
            printf("Program terminated successfully.\n");
            return 0;
            
            default:
            printf("Please Select 1-3 option only ----\n");
        }
    }
}