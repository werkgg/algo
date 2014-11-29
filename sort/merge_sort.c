#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _merge(void *base, size_t p, size_t q, size_t r, size_t size,
        int (*compar)(const void *, const void *))
{
    size_t n1 = q-p;
    size_t n2 = r-q;
    void *left = malloc(n1*size);
    void *right = malloc(n2*size);
    memcpy(left, base+p*size, n1*size);
    memcpy(right, base+q*size, n2*size);
    size_t i,j,k;
    // I want to use custom compare, so not use sentinel card
    for(k=p,i=0,j=0; k<r; k++ )
    {
        if(i<n1&&(j>=n2||compar(right+j*size, left+i*size)>0))
        {
            memcpy(base+k*size, left+i*size, size);
            i++;
        }
        else
        {
            memcpy(base+k*size, right+j*size, size);
            j++;
        }
    }
}

void _mergesort(void *base, size_t p, size_t r, size_t size,
        int (*compar)(const void *, const void *))
{
    if(r-p > 1)
    {
        size_t q = (p+r)/2;
        _mergesort(base,p,q,size,compar);
        _mergesort(base,q,r,size,compar);
        _merge(base,p,q,r,size,compar);
    }
}

void merge_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *))
{
    _mergesort(base,0,nmemb,size,compar);
}
/*
int compar(const void *i, const void *j)
{
    int r = *(int *)i - *(int *)j;
    return r;
}

int main(){
    int i;
    int a[10]={1,3,4,5,6,2,9,7,8,0};
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    merge_sort(&a[0],10,sizeof(int),compar);
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
*/
