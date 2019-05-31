#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,n,tpm,i,a;
    tpm=-2147483648;
    scanf("%d\n", &n);
    for(i=1; i<=n; i++)
    {
        scanf("%d\n", &a);
        if (tpm<=a)
        {
            x=1;
        }
        else
        {
            x=0; break;
        }
        tpm=a;
    }
    printf("%d\n", x);
    return 0;
}
