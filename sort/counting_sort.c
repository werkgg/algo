#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define KMAX 65535

void counting_sort(long int *a, long int nmemb)
{
    // element must between 1..65535
    long long c[KMAX+1] = {0};
    long int i,j;
    long int * b = (long int *)malloc(nmemb*sizeof(long int));
    memcpy(b,a,nmemb*sizeof(long int));
    for(j=0;j<nmemb;j++)
    {
        c[b[j]]++;
    }
    for(i=1;i<=KMAX;i++)
    {
        c[i] = c[i]+c[i-1];
    }
    for(j=nmemb-1;j>=0;j--)
    {
        a[c[b[j]]-1]=b[j];
        c[b[j]]--;
    }
    free(b);
}
/*
int main(){
    int i;
    int a[10]={1,3,1,0,6,2,9,7,8,0};
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    counting_sort(&a[0],10);
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
*/
