#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define LOOPNUM 2

extern void insert_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
extern void heap_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
extern void merge_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
extern void quick_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
extern void counting_sort(long int *a, long int nmemb);
extern void radix_sort(long int *a, long int nmemb);

void random_int(long int * base, long int num)
{
    long int i=0;
    long int key;
    for(i=0;i<num;i++)
    {
        key = random()%65535 + 1;
        base[i] = key;
    }
}

int compar_int(const void *i, const void *j)
{
    int r = *(int *)i - *(int *)j;
    return r;
}

int main(void)
{
    srand(time(NULL));
    long int num,exp,i,j;
    struct timeval tv_before, tv_after;
    for(exp=3;exp<4;exp+=3)
    {
        num = 1<<exp;
        long long int usec;
        printf("=======Sort 2^%ld numbers======\n",exp);
        long int * numlist = (long *)malloc(num*sizeof(long int));

        // insert_sort
        printf("\n==Insert Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_int(numlist,num);
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }

            gettimeofday(&tv_before,NULL);
            insert_sort(numlist,num,sizeof(long int),compar_int);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }
        }
        printf("Insert Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

        // quick_sort
        printf("\n==Quick Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Quick Sort Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_int(numlist,num);
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }

            gettimeofday(&tv_before,NULL);
            quick_sort(numlist,num,sizeof(long int),compar_int);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }
        }
        printf("Quick Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

        // merge_sort
        printf("\n==Merge Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_int(numlist,num);
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }

            gettimeofday(&tv_before,NULL);
            merge_sort(numlist,num,sizeof(long int),compar_int);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }
        }
        printf("Merge Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

        // counting_sort
        printf("\n==Counting Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_int(numlist,num);
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }

            gettimeofday(&tv_before,NULL);
            counting_sort(numlist,num);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }
        }
        printf("Counting Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

        // radix_sort
        printf("\n==Radix Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_int(numlist,num);
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }

            gettimeofday(&tv_before,NULL);
            radix_sort(numlist,num);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%ld%c",numlist[i],i==num-1?'\n':'\t');
            }
        }
        printf("Radix Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);



   }
    return 0;
}
