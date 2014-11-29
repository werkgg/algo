#include<stdio.h>
#define BASE 10

void radix_sort(long int *a, long int nmemb)
{
    long int i, b[nmemb], m = a[0], exp = 1;
    for (i = 1; i < nmemb; i++)
    {
        if (a[i] > m)
        {
            m = a[i];
        }
    }
    while (m / exp > 0)
    {
        long int bucket[BASE] = { 0 };
        for (i = 0; i < nmemb; i++)
        {
            bucket[(a[i] / exp) % BASE]++;
        }
        for (i = 1; i < BASE; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        for (i = nmemb - 1; i >= 0; i--)
        {
            b[--bucket[(a[i] / exp) % BASE]] = a[i];
        }
        for (i = 0; i < nmemb; i++)
        {
            a[i] = b[i];
        }
        exp *= BASE;
    }
}
/*
   int main()
   {
   int i;
   long int a[10]={111,333,109,8888,65535,789,9999,7,8,0};
   for(i=0;i<10;i++)
   {
   printf("%ld ",a[i]);
   }
   printf("\n");
   radix_sort(&a[0],10);
   for(i=0;i<10;i++)
   {
   printf("%ld ",a[i]);
   }
   return 0;
   }
*/
