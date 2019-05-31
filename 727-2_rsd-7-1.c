#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int sorting_function(int *arr, int left, int right)
{
    int l=left, r=right, tmp;
    int M= arr[(l+r)/2];
    while (l <= r)
    {
    while (arr[l] < M)
      l++;
    while (arr[r] > M)
      r--;
    if (l <= r)
      {
          tmp=arr[l];
          arr[l]=arr[r];
          arr[r]=tmp;
          l++; r--;
      }
    }
    if (left<r) sorting_function(arr, left, r);
    if (right>l) sorting_function(arr, l, right);
    return 0;
}
int main()
{
    int *array;
    int i, n;
    scanf("%d", &n);
    array=(int*)malloc(n * sizeof(int));
    for (i=0; i<n; i++) scanf("%d", &array[i]);
    sorting_function(array, 0, n-1);
    for (i=0; i<n-1; i++) printf("%d ", array[i]);
    printf("%d\n", array[i]);
    return 0;
}
