#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)                    \
    do                                      \
{                                           \
    register size_t __size = (size);        \
    register char *__a = (a), *__b = (b);   \
    do                                      \
    {                                       \
        char __tmp = *__a;                  \
        *__a++ = *__b;                      \
        *__b++ = __tmp;                     \
    } while (--__size > 0);                 \
} while (0)


size_t _partition(void *base, size_t start, size_t end, size_t size,
        int (*compar)(const void *, const void *))
{
    void *x = base+end*size;
    size_t i, j;
    i = start;
    for(j=start; j<end; j++)
    {
        if(compar(x, base+j*size) >=0 )
        {
            SWAP(base+i*size, base+j*size, size);
            i++;
        }
    }
    SWAP(base+i*size, x, size);
    return i;
}

void _quicksort(void *base, size_t start, size_t end, size_t size,
        int (*compar)(const void *, const void *))
{
    if(start < end)
    {
        size_t p = _partition(base, start, end, size, compar);
        if(p>0)
            _quicksort(base, start, p-1, size, compar);
        _quicksort(base, p+1, end, size, compar);
    }
}

void quick_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *))
{
    _quicksort(base, 0, nmemb-1, size, compar);
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
    quick_sort(&a[0],10,sizeof(int),compar);
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
*/
