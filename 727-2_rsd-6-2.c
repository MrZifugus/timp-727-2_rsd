#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int sorting_function(int *arr, int arr_len)
{
    int Swap=0,tmp;
    int i,k,j;
    for(k=arr_len/2; k>0; k /= 2)
        for (i=k; i< arr_len; i++)
        {
            tmp=arr[i];
            for (j=i; j >= k; j -= k)
            {
                Swap++;
                if (tmp < arr[j-k])
                {
                    Swap++;
                    arr[j] = arr[j-k];
                }
                else break;
            }
            arr[j]=tmp;
        }
		return Swap;
}

int main()
{
    int *array;
    int n,i,Act;
    scanf("%d", &n);
    array = (int*)malloc(n * sizeof(int));
    for (i = 0; i<n; i++)
  {
    scanf("%d", &array[i]);
  }
    Act=sorting_function(array, n);
    for (i = 0; i<n; i++)
  {
    printf("%d", array[i]);
    if (i<n-1) printf(" ");
  }
   printf("\n");
   return 0;
}
