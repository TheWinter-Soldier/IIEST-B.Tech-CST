#include <stdio.h>

int RecursiveBinarySearch(int Arr[],int Low_index,int End_index,int x) {
    if(End_index >= Low_index) {
        int Mid = Low_index + (End_index-Low_index)/2;

        if(Arr[Mid] == x) return Mid;
        else if(Arr[Mid] > x) return RecursiveBinarySearch(Arr,Low_index,Mid-1,x);
        else return RecursiveBinarySearch(Arr,Mid+1,End_index,x);
    }
    else return -1;
}

int main() {
   int a[] = {2,5,7,19,26,33,56,61,70,89}, n=10, Element, found_index;
   printf("We have an array. Enter a key element to check if it's in the array: ");
   scanf("%d",&Element);

   found_index = RecursiveBinarySearch(a,0,n-1,Element);

   if(found_index == -1) printf("Element not found in the array.\n");
   else printf("Element found at index %d.\n",found_index);
   
   return 0;
}