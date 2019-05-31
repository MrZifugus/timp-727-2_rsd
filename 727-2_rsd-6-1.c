#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int sorting_function(int *arr, int arr_len)
{
    double FT=1.247,igh;
    int Ig=arr_len-1;
    int Swap=0,tmp;
    while (Ig >= 1)
		{
			for (int i = 0; i + Ig < arr_len; ++i)
			{
				if (arr[i] > arr[i + Ig])
				{
				    tmp=arr[i];
				    arr[i]=arr[i+Ig];
				    arr[i+Ig]=tmp;
					Swap++;
				}
			}

			Ig=Ig/FT;
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
