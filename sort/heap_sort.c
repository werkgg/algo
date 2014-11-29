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

void _max_heapify(void *base, size_t i, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *))
{
    size_t l = 2 * i + 1;
    size_t r = 2 * i + 2;
    size_t largest;
    if(l < nmemb && compar(base+l*size, base+i*size) > 0)
    {
        largest = l;

    }else
    {
        largest = i;
    }
    if(r < nmemb && compar(base+r*size, base+largest*size) > 0)
    {
        largest = r;
    }
    if(largest != i)
    {
        SWAP(base+i*size, base+largest*size, size);
        _max_heapify(base, largest, nmemb, size, compar);
    }
}

void _build_max_heap(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *))
{
    size_t i;
    for(i=nmemb/2; i>0; i--)
    {
        _max_heapify(base, i, nmemb, size, compar);
    }
    _max_heapify(base,0,nmemb,size,compar);
}


void heap_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *))
{
    _build_max_heap(base, nmemb, size, compar);
    size_t i;
    for(i=nmemb-1; i>0; i--)
    {
        SWAP(base, base+i*size, size);
        _max_heapify(base, 0, i, size, compar);
    }
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
    heap_sort(&a[0],10,sizeof(int),compar);
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
*/
