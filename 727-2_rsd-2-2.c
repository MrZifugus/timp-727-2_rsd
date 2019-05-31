#include <stdio.h>

int main()
{
    int x,n,i,a;
    n=0;
    scanf("%d", &x);
    for(i=1; i<=x; i++)
    {
        scanf("%d", &a);
        n=n+(a-i);
    }
    printf("%d\n", n);
    return 0;
}
