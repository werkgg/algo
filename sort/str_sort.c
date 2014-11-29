#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define LOOPNUM 2
#define STRLEN 16

extern void insert_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
extern void heap_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
extern void merge_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
extern void quick_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));

void random_str(char ** s, long int num)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    long int i;
    int j,len;
    for(i=0;i<num;i++)
    {
        len = rand()%STRLEN + 1;
        for(j=0;j<len;j++)
        {
            s[i][j] = alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        s[i][len] = 0;
    }
}

int compar_str(const void *i, const void *j)
{
    int r = strcmp(*(const char **)i, *(const char **)j);
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
        char ** strlist = (char **)malloc(num*sizeof(char*));
        long int k;
        for(k=0;k<num;k++)strlist[k]=(char *)malloc(STRLEN*sizeof(char));

        // insert_sort
        printf("\n==Insert Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_str(strlist,num);
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }

            gettimeofday(&tv_before,NULL);
            insert_sort(strlist,num,sizeof(char*),compar_str);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }
        }
        printf("Insert Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

        // heap_sort
        printf("\n==Heap Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_str(strlist,num);
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }

            gettimeofday(&tv_before,NULL);
            heap_sort(strlist,num,sizeof(char*),compar_str);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }
        }
        printf("Heap Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

        // merge_sort
        printf("\n==Merge Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_str(strlist,num);
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }

            gettimeofday(&tv_before,NULL);
            merge_sort(strlist,num,sizeof(char*),compar_str);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }
        }
        printf("Merge Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

        // quick_sort
        printf("\n==Quick Sort==\n");
        for(j=0,usec=0;j<LOOPNUM;j++)
        {
            printf("\n==Quick Sort Loop %ld ==\n",j);
            printf("--------Original--------\n");
            random_str(strlist,num);
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }

            gettimeofday(&tv_before,NULL);
            quick_sort(strlist,num,sizeof(char*),compar_str);
            gettimeofday(&tv_after,NULL);
            usec += (tv_after.tv_usec+tv_after.tv_sec*1e6) - (tv_before.tv_usec+tv_before.tv_sec*1e6);

            printf("--------Sorted----------\n");
            for(i=0;i<num;i++)
            {
                printf("%s\n",strlist[i]);
            }
        }
        printf("Quick Sort Average Time Spend on Sorting 2^%ld Numbers: %lld usec\n\n",exp,usec/LOOPNUM);

    }
    return 0;
}
