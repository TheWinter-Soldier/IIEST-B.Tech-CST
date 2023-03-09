#include <stdio.h>

int RecursiveBinarySearch(int Arr[],int Low_index,int End_index,int x) {
    int i, j, y;

    for(i=0;i < End_index+1;++i) {
        for(j=i+1;j < End_index+1;++j) {
            if(Arr[i] > Arr[j]) {
                y =  Arr[i];
                Arr[i] = Arr[j];
                Arr[j] = y;
            }
        }
    }

    if(End_index >= Low_index) {
        int Mid = Low_index + (End_index-Low_index)/2;

        if(Arr[Mid] == x) return Mid;
        else if(Arr[Mid] > x) return RecursiveBinarySearch(Arr,Low_index,Mid-1,x);
        else return RecursiveBinarySearch(Arr,Mid+1,End_index,x);
    }
    else return -1;
}

int main() {
   int a[100], n, i, Element, found_index;
   printf("Enter the number of elements in the array: ");
   scanf("%d",&n);
   printf("Enter the elements in the array: ");
   for(i=0;i<n;i++) {
       scanf("%d",&a[i]);
   }
   
   printf("Enter a key element to check if it's in the array: ");
   scanf("%d",&Element);

   found_index = RecursiveBinarySearch(a,0,n-1,Element);

   if(found_index == -1) printf("Element not found in the array.\n");
   else printf("Element belongs to the array.\n");
   
   
   return 0;
}